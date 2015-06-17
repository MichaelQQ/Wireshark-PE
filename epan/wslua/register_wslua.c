/* This file is automatically generated by make-reg.pl; do not edit! */

#include "config.h"
#include "wslua.h"

#include "lua_bitop.h"

static void wslua_reg_module(lua_State* L, const char *name _U_, lua_CFunction func) { 
	lua_pushcfunction(L, func);
	lua_call(L, 0, 0);
}

void wslua_register_classes(lua_State* L) { 
	wslua_reg_module(L, "ByteArray", ByteArray_register);
	wslua_reg_module(L, "Tvb", Tvb_register);
	wslua_reg_module(L, "TvbRange", TvbRange_register);
	wslua_reg_module(L, "Pref", Pref_register);
	wslua_reg_module(L, "Prefs", Prefs_register);
	wslua_reg_module(L, "ProtoField", ProtoField_register);
	wslua_reg_module(L, "ProtoExpert", ProtoExpert_register);
	wslua_reg_module(L, "Proto", Proto_register);
	wslua_reg_module(L, "Dissector", Dissector_register);
	wslua_reg_module(L, "DissectorTable", DissectorTable_register);
	wslua_reg_module(L, "Int64", Int64_register);
	wslua_reg_module(L, "UInt64", UInt64_register);
	wslua_reg_module(L, "TreeItem", TreeItem_register);
	wslua_reg_module(L, "NSTime", NSTime_register);
	wslua_reg_module(L, "Address", Address_register);
	wslua_reg_module(L, "Column", Column_register);
	wslua_reg_module(L, "Columns", Columns_register);
	wslua_reg_module(L, "PrivateTable", PrivateTable_register);
	wslua_reg_module(L, "Pinfo", Pinfo_register);
	wslua_reg_module(L, "Listener", Listener_register);
	wslua_reg_module(L, "ProgDlg", ProgDlg_register);
	wslua_reg_module(L, "TextWindow", TextWindow_register);
	wslua_reg_module(L, "Dir", Dir_register);
	wslua_reg_module(L, "FieldInfo", FieldInfo_register);
	wslua_reg_module(L, "Field", Field_register);
	wslua_reg_module(L, "File", File_register);
	wslua_reg_module(L, "CaptureInfo", CaptureInfo_register);
	wslua_reg_module(L, "CaptureInfoConst", CaptureInfoConst_register);
	wslua_reg_module(L, "FrameInfo", FrameInfo_register);
	wslua_reg_module(L, "FrameInfoConst", FrameInfoConst_register);
	wslua_reg_module(L, "FileHandler", FileHandler_register);
	wslua_reg_module(L, "Struct", Struct_register);
	wslua_reg_module(L, "PseudoHeader", PseudoHeader_register);
	wslua_reg_module(L, "Dumper", Dumper_register);
	wslua_reg_module(L, "bit", luaopen_bit);
	lua_pop(L,1);
	wslua_reg_module(L, "GRegex", luaopen_rex_glib);
}

void wslua_register_functions(lua_State* L) {
	WSLUA_REGISTER_FUNCTION(register_postdissector); 
	WSLUA_REGISTER_FUNCTION(dissect_tcp_pdus); 
	WSLUA_REGISTER_FUNCTION(gui_enabled); 
	WSLUA_REGISTER_FUNCTION(register_menu); 
	WSLUA_REGISTER_FUNCTION(new_dialog); 
	WSLUA_REGISTER_FUNCTION(retap_packets); 
	WSLUA_REGISTER_FUNCTION(copy_to_clipboard); 
	WSLUA_REGISTER_FUNCTION(open_capture_file); 
	WSLUA_REGISTER_FUNCTION(get_filter); 
	WSLUA_REGISTER_FUNCTION(set_filter); 
	WSLUA_REGISTER_FUNCTION(set_color_filter_slot); 
	WSLUA_REGISTER_FUNCTION(apply_filter); 
	WSLUA_REGISTER_FUNCTION(reload); 
	WSLUA_REGISTER_FUNCTION(browser_open_url); 
	WSLUA_REGISTER_FUNCTION(browser_open_data_file); 
	WSLUA_REGISTER_FUNCTION(get_version); 
	WSLUA_REGISTER_FUNCTION(format_date); 
	WSLUA_REGISTER_FUNCTION(format_time); 
	WSLUA_REGISTER_FUNCTION(report_failure); 
	WSLUA_REGISTER_FUNCTION(critical); 
	WSLUA_REGISTER_FUNCTION(warn); 
	WSLUA_REGISTER_FUNCTION(message); 
	WSLUA_REGISTER_FUNCTION(info); 
	WSLUA_REGISTER_FUNCTION(debug); 
	WSLUA_REGISTER_FUNCTION(loadfile); 
	WSLUA_REGISTER_FUNCTION(dofile); 
	WSLUA_REGISTER_FUNCTION(register_stat_cmd_arg); 
	WSLUA_REGISTER_FUNCTION(all_field_infos); 
	WSLUA_REGISTER_FUNCTION(register_filehandler); 
	WSLUA_REGISTER_FUNCTION(deregister_filehandler); 
}

