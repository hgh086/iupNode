#include "eventhandle.h"
#include <vector>
#include <exception>

namespace iupnode {
using std::vector;
using v8::Persistent;
using v8::Object;
using v8::Function;
using v8::Local;
using v8::String;
using v8::Integer;
using v8::Number;
using v8::Undefined;
using v8::Isolate;

vector<EventData> eds;

void InitEventData()
{
	EventData ed;
	ed.eType = 0;
	ed.hTarget = NULL;
	ed.caller = NULL;
	ed.func = NULL;
	eds.push_back(ed);
}

int SetCommonCallBack(Ihandle *iTarget, int iType, Persistent<Object> *iCaller, Persistent<Function> *iFunc)
{
	int nRet = 0;
	if ((iType>0) && (iTarget!=NULL) && (iCaller!=NULL) && (iFunc!=NULL))
	{
		EventData ed;
		ed.eType = iType;
		ed.hTarget = iTarget;
		ed.caller = iCaller;
		ed.func = iFunc;
		eds.push_back(ed);
		nRet = 1;
		switch (iType)
		{
			case EVT_DIALOG_CLOSE:
			IupSetCallback(iTarget, "CLOSE_CB", (Icallback)Dialog_Close_CB);
			break;

			case EVT_DIALOG_RESIZE:
			IupSetCallback(iTarget, "RESIZE_CB", (Icallback)Dialog_Resize_CB);
			break;

			case EVT_DIALOG_SHOW:
			IupSetCallback(iTarget, "SHOW_CB", (Icallback)Dialog_Show_CB);
			break;

			case EVT_BUTTON_ACTION:
			IupSetCallback(iTarget, "ACTION", (Icallback)Button_Action_CB);
			break;

			case EVT_TEXT_VALUECHANGED:
			IupSetCallback(iTarget, "VALUECHANGED_CB", (Icallback)Text_ValueChanged_CB);
			break;

			case EVT_LIST_DBLCLICK:
			IupSetCallback(iTarget, "DBLCLICK_CB", (Icallback)List_DblClick_CB);
			break;

			case EVT_LIST_VALUECHANGED:
			IupSetCallback(iTarget, "VALUECHANGED_CB", (Icallback)List_ValueChanged_CB);
			break;

			case EVT_TREE_SELECTION:
			IupSetCallback(iTarget, "SELECTION_CB", (Icallback)Tree_Selection_CB);
			break;

			case EVT_TREE_EXECUTELEAF:
			IupSetCallback(iTarget, "EXECUTELEAF_CB", (Icallback)Tree_ExecuteLeaf_CB);
			break;
			
			case EVT_CANVAS_ACTION:
			IupSetCallback(iTarget, "ACTION", (Icallback)Canvas_Draw_CB);
			break;
			
			case EVT_CANVAS_MOTION:
			IupSetCallback(iTarget, "MOTION_CB", (Icallback)Canvas_Motion_CB);
			break;
			
			case EVT_CANVAS_KEYPRESS:
			IupSetCallback(iTarget, "KEYPRESS_CB", (Icallback)Canvas_KeyPress_CB);
			break;

			default:
			printf("Event type error\n");
			nRet = 0;
			break;
		}
	}
	return nRet;
}

int SearchEventData(Ihandle *iTarget,int iType)
{
	int nRet = -1;
	for (int i=0;i<eds.size();i++)
	{
		if (eds[i].eType==iType && eds[i].hTarget==iTarget)
		{
			nRet = i;
			break;
		}
	}
	return nRet;
}

int Dialog_Close_CB(Ihandle *ih)
{
	int nIndex = SearchEventData(ih,EVT_DIALOG_CLOSE);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		fn->Call(cl,0,NULL);		
	}
	return IUP_CLOSE;
}

int Dialog_Resize_CB(Ihandle *ih, int width, int height)
{
	int nIndex = SearchEventData(ih,EVT_DIALOG_RESIZE);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[2];
		argv[0] = Integer::New(isolate,width);
		argv[1] = Integer::New(isolate,height);
		fn->Call(cl,2,argv);		
	}
	return IUP_DEFAULT;
}

int Dialog_Show_CB(Ihandle *ih, int state)
{
	int nIndex = SearchEventData(ih,EVT_DIALOG_SHOW);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[1];
		argv[0] = Integer::New(isolate,state);
		fn->Call(cl,1,argv);
	}
	return IUP_DEFAULT;
}

int Button_Action_CB(Ihandle *ih)
{
	int nIndex = SearchEventData(ih,EVT_BUTTON_ACTION);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		fn->Call(cl,0,NULL);
	}
	return IUP_DEFAULT;
}

int Text_ValueChanged_CB(Ihandle *ih)
{
	int nIndex = SearchEventData(ih,EVT_TEXT_VALUECHANGED);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		fn->Call(cl,0,NULL);
	}
	return IUP_DEFAULT;
}

int List_DblClick_CB(Ihandle *ih, int item, char *text)
{
	int nIndex = SearchEventData(ih,EVT_LIST_DBLCLICK);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[2];
		argv[0] = Integer::New(isolate,item);
		argv[1] = String::NewFromUtf8(isolate,text);
		fn->Call(cl,2,argv);		
	}
	return IUP_DEFAULT;
}

int List_ValueChanged_CB(Ihandle *ih)
{
	int nIndex = SearchEventData(ih,EVT_LIST_VALUECHANGED);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		fn->Call(cl,0,NULL);
	}
	return IUP_DEFAULT;
}

int Tree_Selection_CB(Ihandle *ih, int id, int status) {
	int nIndex = SearchEventData(ih,EVT_TREE_SELECTION);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[2];
		argv[0] = Integer::New(isolate,id);
		argv[1] = Integer::New(isolate,status);
		fn->Call(cl,2,argv);
	}
	return IUP_DEFAULT;
}

int Tree_ExecuteLeaf_CB(Ihandle *ih, int id) {
	int nIndex = SearchEventData(ih,EVT_TREE_EXECUTELEAF);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[1];
		argv[0] = Integer::New(isolate,id);
		fn->Call(cl,1,argv);
	}
	return IUP_DEFAULT;
}

int Canvas_Draw_CB(Ihandle *ih, float posx, float posy) {
	int nIndex = SearchEventData(ih,EVT_CANVAS_ACTION);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[2];
		argv[0] = Number::New(isolate,(double)posx);
		argv[1] = Number::New(isolate,(double)posy);
		fn->Call(cl,2,argv);		
	}
	return IUP_DEFAULT;
}

int Canvas_Motion_CB(Ihandle *ih, int x, int y, char *status) {
	int nIndex = SearchEventData(ih,EVT_CANVAS_MOTION);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[2];
		argv[0] = Integer::New(isolate,x);
		argv[1] = Integer::New(isolate,y);
		fn->Call(cl,2,argv);		
	}
	return IUP_DEFAULT;
}

int Canvas_KeyPress_CB(Ihandle *ih, int c, int press) {
	int nIndex = SearchEventData(ih,EVT_CANVAS_KEYPRESS);
	if (nIndex>0)
	{
		Isolate* isolate = Isolate::GetCurrent();
		Local<Function> fn = Local<Function>::New(isolate,*(eds[nIndex].func));
		Local<Object> cl = Local<Object>::New(isolate,*(eds[nIndex].caller));
		v8::Handle<v8::Value> argv[1];
		argv[0] = Integer::New(isolate,c);
		fn->Call(cl,1,argv);		
	}
	return IUP_DEFAULT;
}

}
