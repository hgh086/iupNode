#include "tree.h"
#include <stdio.h>
#include <string.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Integer;
using v8::Undefined;
using v8::FunctionTemplate;

ITree::ITree() 
{
	hwnd = NULL;
}
ITree::~ITree() {}

void ITree::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "ITree"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosx", _setPosx);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosy", _setPosy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setSize", _setSize);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setNodeText", _setNodeText);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeText", _getNodeText);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeChildCount", _getNodeChildCount);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeDepth", _getNodeDepth);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeParent", _getNodeParent);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeKind", _getNodeKind);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addBranch", _addBranch);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addLeaf", _addLeaf);
	NODE_SET_PROTOTYPE_METHOD(tpl, "insertBranch", _insertBranch);
	NODE_SET_PROTOTYPE_METHOD(tpl, "insertLeaf", _insertLeaf);
	NODE_SET_PROTOTYPE_METHOD(tpl, "delNode", _delNode);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getNodeCount", _getNodeCount);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getSelection", _getSelection);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getLastAdd", _getLastAdd);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "ITree"),tpl->GetFunction());
}

void ITree::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* obj = new ITree();
	// Create Tree
	obj->hwnd = IupTree();
	// Set Position
	if (args.Length()>0 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CX",*str);
	}
	if (args.Length()>1 && args[1]->IsNumber()) {
		Local<String> tt = args[1]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CY",*str);
	}
	// Set size
	if (args.Length()>3 && args[2]->IsNumber() && args[3]->IsNumber()) {
		int ww = args[2]->Int32Value();
		int hh = args[3]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"%dx%d", ww, hh);
		IupSetStrAttribute(obj->hwnd, "RASTERSIZE", buf);
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_setPosx(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(tr->hwnd,"CX",*str);
	} else {
		printf("setPosx arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ITree::_setPosy(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(tr->hwnd,"CY",*str);
	} else {
		printf("setPosy arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ITree::_setSize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsNumber()) {
		int ww = args[0]->Int32Value();
		int hh = args[1]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"%dx%d", ww, hh);
		IupSetStrAttribute(tr->hwnd, "RASTERSIZE", buf);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_setNodeText(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsString()) {
		int id = args[0]->Int32Value();
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"TITLE%d", id);
		IupSetStrAttribute(tr->hwnd, buf, *str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_getNodeText(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"TITLE%d", id);
		char* sRet = IupGetAttribute(tr->hwnd,buf);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, sRet));
	} else {
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
	}
}

void ITree::_getNodeChildCount(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"CHILDCOUNT%d", id);
		int nRet = IupGetInt(tr->hwnd,buf);
		args.GetReturnValue().Set(Integer::New(isolate, nRet));
	} else {
		args.GetReturnValue().Set(Integer::New(isolate, 0));
	}
}

void ITree::_getNodeDepth(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"DEPTH%d", id);
		int nRet = IupGetInt(tr->hwnd,buf);
		args.GetReturnValue().Set(Integer::New(isolate, nRet));
	} else {
		args.GetReturnValue().Set(Integer::New(isolate, -1));
	}
}

void ITree::_getNodeParent(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"PARENT%d", id);
		int nRet = IupGetInt(tr->hwnd,buf);
		args.GetReturnValue().Set(Integer::New(isolate, nRet));
	} else {
		args.GetReturnValue().Set(Integer::New(isolate, -1));
	}
}

void ITree::_getNodeKind(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"KIND%d", id);
		char* sRet = IupGetAttribute(tr->hwnd,buf);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, sRet));
	} else {
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
	}
}

void ITree::_addBranch(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsString()) {
		int id = args[0]->Int32Value();
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"ADDBRANCH%d", id);
		IupSetStrAttribute(tr->hwnd, buf, *str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_addLeaf(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsString()) {
		int id = args[0]->Int32Value();
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"ADDLEAF%d", id);
		IupSetStrAttribute(tr->hwnd, buf, *str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_insertBranch(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsString()) {
		int id = args[0]->Int32Value();
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"INSERTBRANCH%d", id);
		IupSetStrAttribute(tr->hwnd, buf, *str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_insertLeaf(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsString()) {
		int id = args[0]->Int32Value();
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"INSERTLEAF%d", id);
		IupSetStrAttribute(tr->hwnd, buf, *str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_delNode(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int id = args[0]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"DELNODE%d", id);
		IupSetStrAttribute(tr->hwnd, buf, "SELECTED");
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ITree::_getNodeCount(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	int nRet = IupGetInt(tr->hwnd,"COUNT");
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void ITree::_getSelection(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	int nRet = IupGetInt(tr->hwnd,"VALUE");
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void ITree::_getLastAdd(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ITree* tr = ObjectWrap::Unwrap<ITree>(args.Holder());
	int nRet = IupGetInt(tr->hwnd,"LASTADDNODE");
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

}
