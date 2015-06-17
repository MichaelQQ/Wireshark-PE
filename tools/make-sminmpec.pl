#!/usr/bin/perl -w
# create the sminmpec.c file from
# http://www.iana.org/assignments/enterprise-numbers
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 2004 Gerald Combs
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

use strict;
use File::Spec;

my ($vol, $script_dir, $file) = File::Spec->splitpath( __FILE__ );
my $epan_dir = File::Spec->catpath($vol, $script_dir, '../epan');
chdir($epan_dir) || die("Can't find $epan_dir");

my $in = shift;

$in = "http://www.iana.org/assignments/enterprise-numbers" unless(defined $in);

my @in_lines;
my $revision = '2014-04-27';

my $min_entries = 100;
my $smi_total = 0;

if($in =~ m/^http:/i) {
	eval "require LWP::UserAgent;";
	die "LWP isn't installed. It is part of the standard Perl module libwww." if $@;

	my $agent    = LWP::UserAgent->new;
	$agent->env_proxy;
	$agent->agent("Wireshark make-sminmpec.pl/$revision");

	warn "starting to fetch $in ...\n";

	my $request  = HTTP::Request->new(GET => $in);

	my $result   = $agent->request($request);

	if ($result->code eq 200) {
		warn "done fetching $in\n";
		@in_lines = split /\n/, $result->content;
		open ENFILE, "> enterprise-numbers";

		for (@in_lines) {
			chomp;
			print ENFILE "$_\n";
		}

		close ENFILE;
	} elsif ($result->code eq 304) {
		warn "enterprise-numbers was up-to-date\n";
		open IN, "< enterprise-numbers";
		@in_lines = <IN>;
		close IN;
	} else {
		die "request for $in failed with result code:" . $result->code;
	}

} else {
  open IN, "< $in";
  @in_lines = <IN>;
  close IN;
}


my $body = '';
my $code;
my $prev_code = -1;  ## Assumption: First code in enterprise file is 0;

sub escape_non_ascii {
    my $val = unpack 'C', $_[0];
    return sprintf '\0%.3o',$val;
}


for(@in_lines) {
	s/[\000-\037]//g;
	s/\\/\\\\/g;
	s/"/\\"/g;
	s/([\x80-\xFF])/escape_non_ascii($1)/ge;

	if (/^(\d+)/) {
		$code = sprintf("%5d", $1);
	} if (/^  (\S.*)/ ) {
		my $name = $1;
		if ($code < $prev_code) {
			print STDERR ("Input 'Codes' not sorted in ascending order (or duplicate codes)): $prev_code $code\n");
                        exit 1;
		}
		while ($code > ($prev_code+1)) {
			$prev_code = sprintf("%5d", $prev_code+1);
			$body .= "    { $prev_code, sminmpec_unknown },  /* (Added by Wireshark) */\n";
		}
		$prev_code = $code;
		$body .= "    { $code, \"$name\" },\n";
		$smi_total++;
	}
}

# If this happens check what IANA is serving.
# XXX We already overwrote enterprise-numbers above.
if ($smi_total < $smi_total) { die "Too few SMI entries ($smi_total)\n"; }

open OUT, "> sminmpec.c";

print OUT <<"_SMINMPEC";
/*
 * THIS FILE IS AUTOGENERATED, DO NOT EDIT
 * generated from http://www.iana.org/assignments/enterprise-numbers
 * run "tools/make-sminmpec.pl <infile> <outfile>" to regenerate
 *
 * Note 1: "Gaps" in the iana enterprise-numbers list have been "filled in"
 *       with "(Unknown)" as the name so that direct (indexed) access to
 *       the list is possible.
 *
 * Note 2: We should probably parse "enterprise-numbers" at program start
 *       instead of generating this file.
 */
#include "config.h"

#include <glib.h>

#include <epan/value_string.h>
#include <epan/sminmpec.h>

static const gchar sminmpec_unknown[] = "(Unknown)";

const value_string sminmpec_values[] = {
$body    {    0, NULL}
};

#define array_length(x)	(sizeof x / sizeof x[0])

value_string_ext sminmpec_values_ext = VALUE_STRING_EXT_INIT(sminmpec_values);

_SMINMPEC

close OUT;