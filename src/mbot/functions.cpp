/*

Miranda Scripting Plugin for Miranda-IM
Copyright 2004-2006 Piotr Pawluczuk (www.pawluczuk.info)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include "mbot.h"
#include "functions.h"
#include "config.h"

const char* PHP_ERROR_MSG = "The number of parameters, or their values are incorrect! It's also possible that you called a function which isn't allowed in current stage!";
const char* PHP_ERROR_EXECUTION = "An error occured while executing your PHP statement/script!\nThere might be some error info in /mbot/(profile)_dbg.txt";
const char* PHP_ERROR_TITLE = "ERROR";
const char* PHP_WARN_INVALID_PARAMS = "Invalid parameters given!";

/******************************************
 * Load/Unload                            *
 ******************************************/
PHP_MINIT_FUNCTION(mb_module_entry);

/* function table */
zend_function_entry mb_functions[] =
{
	PHP_FE(mb_SelfRegister,NULL)
	PHP_FE(mb_SelfEnable,NULL)
	PHP_FE(mb_SelfSetInfo,NULL)
	//scheduler
	PHP_FE(mb_SchReg,NULL)
	PHP_FE(mb_SchModify,NULL)
	PHP_FE(mb_SchUnreg,NULL)
	PHP_FE(mb_SchEnable,NULL)
	PHP_FE(mb_SchList,NULL)
	//misc
	PHP_FE(mb_MsgBox,NULL)
	PHP_FE(mb_Echo,NULL)
	//msgs
	PHP_FE(mb_MsgSend,NULL)
	PHP_FE(mb_MsgSetBody,NULL)
	//menu
	PHP_FE(mb_MenuAdd,NULL)
	PHP_FE(mb_MenuModify,NULL)
	//clist
	PHP_FE(mb_CListEventAdd,NULL)
	//system
	PHP_FE(mb_SysEnumModules,NULL)
	PHP_FE(mb_SysEnumProtocols,NULL)
	PHP_FE(mb_SysEnumHandlers,NULL)
	PHP_FE(mb_SysGetMirandaDir,NULL)
	PHP_FE(mb_SysGetProfileName,NULL)
	PHP_FE(mb_SysTranslate,NULL)
	PHP_FE(mb_SysQuit,NULL)
	PHP_FE(mb_SysCallService,NULL)
	PHP_FE(mb_SysCallProtoService,NULL)
	PHP_FE(mb_SysCallContactService,NULL)
	PHP_FE(mb_SysGetString,NULL)
	PHP_FE(mb_SysGetNumber,NULL)
	PHP_FE(mb_SysGetPointer,NULL)
	PHP_FE(mb_SysPutString,NULL)
	PHP_FE(mb_SysPutNumber,NULL)
	PHP_FE(mb_SysMalloc,NULL)
	PHP_FE(mb_SysFree,NULL)
	PHP_FE(mb_SysGlobalAlloc,NULL)
	PHP_FE(mb_SysGlobalFree,NULL)
	PHP_FE(mb_SysMemCpy,NULL)
	PHP_FE(mb_SysBeginThread,NULL)
	PHP_FE(mb_SysLoadModule,NULL)
	PHP_FE(mb_SysUnLoadModule,NULL)
	PHP_FE(mb_SysManageScript,NULL)
	PHP_FE(mb_SysShallDie,NULL)
	PHP_FE(mb_SysCreateService,NULL)
	PHP_FE(mb_SysHookEvent,NULL)
	PHP_FE(mb_SysGetProcAddr,NULL)
	PHP_FE(mb_SysCallProc,NULL)
	//console
	PHP_FE(mb_ConsoleShow,NULL)
	PHP_FE(mb_ConsoleClear,NULL)
	//protocols
	PHP_FE(mb_PGetMyStatus,NULL)
	PHP_FE(mb_PSetMyStatus,NULL)
	PHP_FE(mb_PSetMyAwayMsg,NULL)
	PHP_FE(mb_PGetCaps,NULL)
	//contact/settings
	PHP_FE(mb_CSettingGet,NULL)
	PHP_FE(mb_CSettingSet,NULL)
	PHP_FE(mb_CGetAwayMsg,NULL)
	PHP_FE(mb_CSettingAdd,NULL)
	PHP_FE(mb_CSettingDel,NULL)
	PHP_FE(mb_CSettingEnum,NULL)
	PHP_FE(mb_CGetStatus,NULL)
	PHP_FE(mb_CGetUIN,NULL)
	PHP_FE(mb_CGetProto,NULL)
	PHP_FE(mb_CDelete,NULL)
	PHP_FE(mb_CGetDisplayName,NULL)
	PHP_FE(mb_CIsOnList,NULL)
	PHP_FE(mb_CFindFirst,NULL)
	PHP_FE(mb_CFindNext,NULL)
	PHP_FE(mb_CFindByUIN,NULL)
	PHP_FE(mb_CSetApparentMode,NULL)
	PHP_FE(mb_CAddNew,NULL)
	PHP_FE(mb_CGetInfo,NULL)
	PHP_FE(mb_CAddAuth,NULL)
	PHP_FE(mb_CAddSearch,NULL)
	PHP_FE(mb_CSendTypingInfo,NULL)
	//auth
	PHP_FE(mb_AuthGetInfo,NULL)
	PHP_FE(mb_AuthDeny,NULL)
	PHP_FE(mb_AuthAccept,NULL)
	PHP_FE(mb_AuthStore,NULL)
	//events
	PHP_FE(mb_EventGetCount,NULL)
	PHP_FE(mb_EventFindFirst,NULL)
	PHP_FE(mb_EventFindFirstUnread,NULL)
	PHP_FE(mb_EventFindNext,NULL)
	PHP_FE(mb_EventFindPrev,NULL)
	PHP_FE(mb_EventFindLast,NULL)
	PHP_FE(mb_EventGetData,NULL)
	PHP_FE(mb_EventDel,NULL)
	PHP_FE(mb_EventMarkRead,NULL)
	PHP_FE(mb_EventAdd,NULL)
	//sounds
	PHP_FE(mb_SoundPlay,NULL)
	PHP_FE(mb_SoundAdd,NULL)
	PHP_FE(mb_SoundAddEx,NULL)
	PHP_FE(mb_SoundDel,NULL)
	PHP_FE(mb_SoundSet,NULL)
	//popups
	PHP_FE(mb_PUMsg,NULL)
	PHP_FE(mb_PUAdd,NULL)
	PHP_FE(mb_PUAddEx,NULL)
	PHP_FE(mb_PUSystem,NULL)
	//icons
	PHP_FE(mb_IconLoadSys,NULL)
	PHP_FE(mb_IconLoadSkin,NULL)
	PHP_FE(mb_IconLoadProto,NULL)
	PHP_FE(mb_IconLoadSkinnedProto,NULL)
	PHP_FE(mb_IconDestroy,NULL)
	//search
	PHP_FE(mb_SearchBasic,NULL)
	PHP_FE(mb_SearchByEmail,NULL)
	PHP_FE(mb_SearchByName,NULL)
	//dialogs
	PHP_FE(mb_DlgGetFile,NULL)
	PHP_FE(mb_DlgGetFileMultiple,NULL)
	//irc
	PHP_FE(mb_IrcGetGuiDataIn,NULL)
	PHP_FE(mb_IrcSetGuiDataIn,NULL)
	PHP_FE(mb_IrcSetGuiDataOut,NULL)
	PHP_FE(mb_IrcInsertRawIn,NULL)
	PHP_FE(mb_IrcInsertRawOut,NULL)
	PHP_FE(mb_IrcInsertGuiIn,NULL)
	PHP_FE(mb_IrcInsertGuiOut,NULL)
	PHP_FE(mb_IrcGetData,NULL)
	PHP_FE(mb_IrcPostMessage,NULL)

	PHP_FE(mb_DlgCreate,NULL)
	PHP_FE(mb_DlgRun,NULL)
	PHP_FE(mb_DlgGet,NULL)
	PHP_FE(mb_DlgAddControl,NULL)
	PHP_FE(mb_DlgGetText,NULL)
	PHP_FE(mb_DlgSetText,NULL)
	PHP_FE(mb_DlgGetInt,NULL)
	PHP_FE(mb_DlgGetIdByParam,NULL)
	PHP_FE(mb_DlgSendMsg,NULL)
	PHP_FE(mb_DlgSetCallbacks,NULL)
	PHP_FE(mb_DlgSetTimer,NULL)
	PHP_FE(mb_DlgKillTimer,NULL)

	PHP_FE(mb_DlgListAddItem,NULL)
	PHP_FE(mb_DlgListDelItem,NULL)
	PHP_FE(mb_DlgListSetItem,NULL)
	PHP_FE(mb_DlgListGetItem,NULL)
	PHP_FE(mb_DlgListGetSel,NULL)
	PHP_FE(mb_DlgListAddCol,NULL)

	PHP_FE(mb_DlgComboAddItem,NULL)
	PHP_FE(mb_DlgComboDelItem,NULL)
	PHP_FE(mb_DlgComboGetItem,NULL)
	PHP_FE(mb_DlgComboGetItemData,NULL)
	PHP_FE(mb_DlgComboGetSel,NULL)

	PHP_FE(mb_DlgGetHWND,NULL)
	PHP_FE(mb_DlgMove,NULL)
	PHP_FE(mb_DlgGetString,NULL)

	//files
	PHP_FE(mb_FileInitSend,NULL)
	PHP_FE(mb_FileAccept,NULL)
	PHP_FE(mb_FileDeny,NULL)
	PHP_FE(mb_FileStore,NULL)
	PHP_FE(mb_FileCancel,NULL)
	PHP_FE(mb_FileGetInfo,NULL)
	//asus
	PHP_FE(mb_AsusExt,NULL)

	ZEND_FALIAS(mbox,mb_MsgBox,NULL)
	{NULL, NULL, NULL}
};
/* compiled module information */
zend_module_entry mb_module_entry =
{
	STANDARD_MODULE_HEADER,
	"Miranda Scripting Plugin",
	mb_functions,
	PHP_MINIT(mb_module_entry),
	NULL,NULL,NULL,NULL,
	NO_VERSION_YET,
	STANDARD_MODULE_PROPERTIES
};

void* mv_module_entry = (void*)&mb_module_entry;

/* init_function */
PHP_MINIT_FUNCTION(mb_module_entry)
{
	extern DWORD g_mbot_version;
	extern int g_res_dlg_id;
	extern char* g_res_dlg_name;

	g_res_dlg_id = zend_register_list_destructors_ex(help_dlg_destruction_handler,NULL,(char*)g_res_dlg_name,module_number);

	try
	{
		//events
		REGISTER_LONG_CONSTANT("MB_EVENT_MSG_IN",MB_EVENT_MSG_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_MSG_OUT",MB_EVENT_MSG_OUT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_URL_IN",MB_EVENT_URL_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_AUTH_IN",MB_EVENT_AUTH_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_AWAY_MSG_OUT",MB_EVENT_AWAY_MSG_OUT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_AWAY_MSG_REQ",MB_EVENT_AWAY_MSG_REQ,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_NEW_CSTATUS",MB_EVENT_NEW_CSTATUS,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_NEW_MYSTATUS",MB_EVENT_NEW_MYSTATUS,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_COMMAND",MB_EVENT_COMMAND,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_STARTUP",MB_EVENT_STARTUP,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_SHUTDOWN",MB_EVENT_SHUTDOWN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_USER_TYPING",MB_EVENT_USER_TYPING,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_AWAY_MSG_ICQ",MB_EVENT_AWAY_MSG_ICQ,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_MENU_COMMAND",MB_EVENT_MENU_COMMAND,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_DUMMY",MB_EVENT_MENU_COMMAND,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_EXTERNAL",MB_EVENT_EXTERNAL,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_FILE_IN",MB_EVENT_FILE_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IRC_EVENT_GUI_IN",IRC_EVENT_GUI_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IRC_EVENT_GUI_OUT",IRC_EVENT_GUI_OUT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IRC_EVENT_RAW_IN",IRC_EVENT_RAW_IN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IRC_EVENT_RAW_OUT",IRC_EVENT_RAW_OUT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MB_EVENT_CONFIG",MB_EVENT_CONFIG,CONST_CS|CONST_PERSISTENT);
		//mbot version
		REGISTER_LONG_CONSTANT("MBOT_VERSION",g_mbot_version,CONST_CS|CONST_PERSISTENT);
		REGISTER_STRING_CONSTANT("MBOT_TIMESTAMP",__TIMESTAMP__,CONST_CS|CONST_PERSISTENT);
		//event types
		REGISTER_LONG_CONSTANT("EVENTTYPE_MESSAGE",EVENTTYPE_MESSAGE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("EVENTTYPE_URL",EVENTTYPE_URL,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("EVENTTYPE_CONTACTS",EVENTTYPE_CONTACTS,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("EVENTTYPE_ADDED",EVENTTYPE_ADDED,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("EVENTTYPE_AUTHREQUEST",EVENTTYPE_AUTHREQUEST,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("EVENTTYPE_FILE",EVENTTYPE_FILE,CONST_CS|CONST_PERSISTENT);
		//database types
		REGISTER_LONG_CONSTANT("DBVT_BYTE",DBVT_BYTE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_WORD",DBVT_WORD,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_DWORD",DBVT_DWORD,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_ASCIIZ",DBVT_ASCIIZ,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_BLOB",DBVT_BLOB,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_UTF8",DBVT_UTF8,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVT_WCHAR",DBVT_WCHAR,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("DBVTF_VARIABLELENGTH",DBVTF_VARIABLELENGTH,CONST_CS|CONST_PERSISTENT);
		//status ids
		REGISTER_LONG_CONSTANT("ID_STATUS_OFFLINE",40071,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_ONLINE",40072,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_AWAY",40073,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_DND",40074,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_NA",40075,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_OCCUPIED",40076,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_FREECHAT",40077,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_INVISIBLE",40078,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_ONTHEPHONE",40079,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_OUTTOLUNCH",40080,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("ID_STATUS_IDLE",40081,CONST_CS|CONST_PERSISTENT);
		//icons
		REGISTER_LONG_CONSTANT("IDI_APPLICATION",1,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_ASTERISK",2,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_ERROR",3,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_EXCLAMATION",4,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_HAND",5,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_INFORMATION",6,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_QUESTION",7,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_WARNING",8,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("IDI_WINLOGO",9,CONST_CS|CONST_PERSISTENT);
		//skin icons
		REGISTER_LONG_CONSTANT("SKINICON_EVENT_MESSAGE",SKINICON_EVENT_MESSAGE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_EVENT_URL",SKINICON_EVENT_URL,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_EVENT_FILE",SKINICON_EVENT_FILE,CONST_CS|CONST_PERSISTENT);
		//other icons
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_MIRANDA",SKINICON_OTHER_MIRANDA,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_EXIT",SKINICON_OTHER_EXIT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_SHOWHIDE",SKINICON_OTHER_SHOWHIDE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_GROUPOPEN",SKINICON_OTHER_GROUPOPEN,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_GROUPSHUT",SKINICON_OTHER_GROUPSHUT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_OTHER_USERONLINE",SKINICON_OTHER_USERONLINE,CONST_CS|CONST_PERSISTENT);
		//status mode icons
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_OFFLINE",SKINICON_STATUS_OFFLINE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_ONLINE",SKINICON_STATUS_ONLINE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_AWAY",SKINICON_STATUS_AWAY,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_NA",SKINICON_STATUS_NA,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_OCCUPIED",SKINICON_STATUS_OCCUPIED,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_DND",SKINICON_STATUS_DND,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_FREE4CHAT",SKINICON_STATUS_FREE4CHAT,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_INVISIBLE",SKINICON_STATUS_INVISIBLE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_ONTHEPHONE",SKINICON_STATUS_ONTHEPHONE,CONST_CS|CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("SKINICON_STATUS_OUTTOLUNCH",SKINICON_STATUS_OUTTOLUNCH,CONST_CS|CONST_PERSISTENT);
		return SUCCESS;
	}catch(...){
		return FAILURE;
	}
}