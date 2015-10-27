#ifndef IUP_EVENT_HANDLE_H
#define IUP_EVENT_HANDLE_H

#include <iup.h>
#include <node.h>

#define EVT_NULL 0
#define EVT_COMMON_MAP 1
#define EVT_COMMON_UNMAP 2
#define EVT_COMMON_DESTROY 3
#define EVT_COMMON_GETFOCUS 4
#define EVT_COMMON_KILLFOCUS 5
#define EVT_COMMON_ENTERWINDOW 6
#define EVT_COMMON_LEAVEWINDOW 7
#define EVT_COMMON_K_ANY 8
#define EVT_COMMON_HELP 9

#define EVT_DIALOG_CLOSE 21
#define EVT_DIALOG_DROPFILES 22
#define EVT_DIALOG_RESIZE 23
#define EVT_DIALOG_SHOW 24

#define EVT_BUTTON_ACTION 31

#define EVT_TEXT_CARET 36
#define EVT_TEXT_MOTION 37
#define EVT_TEXT_VALUECHANGED 38

#define EVT_LIST_DBLCLICK 41
#define EVT_LIST_VALUECHANGED 42

#define EVT_TAB_TABCHANGE 46
#define EVT_TAB_TABCLOSE 47
#define EVT_TAB_RIGHTCLICK 48

#define EVT_TREE_SELECTION 51
#define EVT_TREE_BRANCHOPEN 52
#define EVT_TREE_BRANCHCLOSE 53
#define EVT_TREE_EXECUTELEAF 54
#define EVT_TREE_RIGHTCLICK 55

#define EVT_CANVAS_ACTION 61 //Redraw
#define EVT_CANVAS_BUTTON 62
#define EVT_CANVAS_MOTION 63
#define EVT_CANVAS_KEYPRESS 64
#define EVT_CANVAS_RESIZE 65
#define EVT_CANVAS_TOUCH 66
#define EVT_CANVAS_MULTITOUCH 67
#define EVT_CANVAS_WHEEL 68

namespace iupnode {

typedef struct tagEventData {
	int eType;
	Ihandle* hTarget;
	v8::Persistent<v8::Object> *caller;	
	v8::Persistent<v8::Function> *func;
} EventData;

void InitEventData();

int SetCommonCallBack(Ihandle *iTarget, int iType, v8::Persistent<v8::Object> *iCaller, v8::Persistent<v8::Function> *iFunc);

int SearchEventData(Ihandle *iTarget,int iType);

int Dialog_Close_CB(Ihandle *ih);
int Dialog_Resize_CB(Ihandle *ih, int width, int height);
int Dialog_Show_CB(Ihandle *ih, int state);

int Button_Action_CB(Ihandle *ih);

int Text_ValueChanged_CB(Ihandle *ih);

int List_DblClick_CB(Ihandle *ih, int item, char *text);
int List_ValueChanged_CB(Ihandle *ih);

int Tree_Selection_CB(Ihandle *ih, int id, int status);
int Tree_ExecuteLeaf_CB(Ihandle *ih, int id);

int Canvas_Draw_CB(Ihandle *ih, float posx, float posy);
int Canvas_Motion_CB(Ihandle *ih, int x, int y, char *status);
int Canvas_KeyPress_CB(Ihandle *ih, int c, int press);

}

#endif