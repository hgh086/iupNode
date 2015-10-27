#include "dialog.h"
#include "eventhandle.h"
#include <string.h>
#include <stdio.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::FunctionTemplate;
using v8::String;
using v8::Integer;
using v8::Function;
using v8::Value;
using v8::Array;
using v8::Persistent;
using v8::Handle;

IDialog::IDialog() 
{
	hwnd = NULL;
	hBox = NULL;
	nWidth = 40;
	nHeight = 30;
}
IDialog::~IDialog() {}

void IDialog::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IDialog"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "show", _show);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTitle", _setTitle);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setCloseCB", _setCloseCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setResizeCB", _setResizeCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setShowCB", _setShowCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setButtonActionCB", _setButtonActionCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTextValueChangedCB", _setTextValueChangedCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setListDblClickCB", _setListDblClickCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setListValueChangedCB", _setListValueChangedCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTreeSelectionCB", _setTreeSelectionCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTreeExecuteLeafCB", _setTreeExecuteLeafCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "redraw", _redraw);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IDialog"),tpl->GetFunction());
}

void IDialog::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* obj = new IDialog();
	if (args.Length()==0) {
		obj->nWidth = 40;
		obj->nHeight = 30;
	} else if (args.Length() == 1) {
		obj->nWidth = args[0]->IsNumber() ? args[0]->Int32Value() : 40;
		obj->nHeight = 30;
	} else if (args.Length() == 2) {
		obj->nWidth = args[0]->IsNumber() ? args[0]->Int32Value() : 40;
		obj->nHeight = args[1]->IsNumber() ? args[1]->Int32Value() : 30;
	} else if (args.Length() > 2) {
		obj->nWidth = args[0]->IsNumber() ? args[0]->Int32Value() : 40;
		obj->nHeight = args[1]->IsNumber() ? args[1]->Int32Value() : 30;
	}
	if (args.Length()>2) {
		int leng = args.Length() - 2;
		Ihandle* *hs = new Ihandle*[leng+1];
		for (int i=2;i<args.Length();i++) {
			if (args[i]->IsObject()) {
				Local<Object> x = Local<Object>::Cast(args[i]);
				CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(x);
				hs[i-2] = ooo->hwnd;
			} else {
				hs[i-2] = 0;
			}
		}
		hs[leng] = 0;
		obj->hBox = IupCboxv(hs);
		delete [] hs;
	} else {
		obj->hBox = IupCbox(0);
	}
	char sProp[64];
	memset(sProp,0,64);
	sprintf(sProp,"%dx%d",obj->nWidth,obj->nHeight);
	IupSetStrAttribute(obj->hBox,"RASTERSIZE",sProp);
	obj->hwnd = IupDialog(obj->hBox);
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_show(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	IupShowXY(dlg->hwnd,IUP_CENTER,IUP_CENTER);
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setTitle(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(dlg->hwnd,"TITLE",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setCloseCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(dlg->hwnd,EVT_DIALOG_CLOSE,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setResizeCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(dlg->hwnd,EVT_DIALOG_RESIZE,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setShowCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(dlg->hwnd,EVT_DIALOG_SHOW,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setButtonActionCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_BUTTON_ACTION,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setTextValueChangedCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_TEXT_VALUECHANGED,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setListDblClickCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_LIST_DBLCLICK,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setListValueChangedCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_LIST_VALUECHANGED,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void IDialog::_setTreeSelectionCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_TREE_SELECTION,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_setTreeExecuteLeafCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (args.Length()==2 && args[0]->IsObject() && args[1]->IsFunction()) {
		Local<Object> xx = Local<Object>::Cast(args[0]);
		CoreObject* ooo = ObjectWrap::Unwrap<CoreObject>(xx);
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[1]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(ooo->hwnd,EVT_TREE_EXECUTELEAF,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_redraw(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (dlg != NULL)
	{
		IupRedraw(dlg->hwnd,1);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IDialog::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IDialog* dlg = ObjectWrap::Unwrap<IDialog>(args.Holder());
	if (dlg != NULL)
	{
		IupDestroy(dlg->hwnd);
		dlg->hBox = NULL;
		dlg->hwnd = NULL;
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}

