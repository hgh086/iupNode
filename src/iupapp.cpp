#include "iupapp.h"
#include <string.h>

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

IupApp::IupApp() 
{
	hwnd = NULL;
}
IupApp::~IupApp() {}

void IupApp::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IupApp"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTopWindow", _setTopWindow);
	NODE_SET_PROTOTYPE_METHOD(tpl, "iupOpen", _iupOpen);
	NODE_SET_PROTOTYPE_METHOD(tpl, "run", _run);
	NODE_SET_PROTOTYPE_METHOD(tpl, "single", _single);
	NODE_SET_PROTOTYPE_METHOD(tpl, "iupClose", _iupClose);
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IupApp"),tpl->GetFunction());
}

void IupApp::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IupApp* obj = new IupApp();
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IupApp::_setTopWindow(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IupApp* app = ObjectWrap::Unwrap<IupApp>(args.Holder());

	args.GetReturnValue().Set(Undefined(isolate));
}

void IupApp::_iupOpen(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IupOpen(0,NULL);
	IupSetGlobal("UTF8MODE","Yes");
	args.GetReturnValue().Set(Undefined(isolate));
}

void IupApp::_run(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	printf("IupIojs run\n");
	IupMainLoop();
	args.GetReturnValue().Set(Undefined(isolate));
}

void IupApp::_single(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	int nRet = IupLoopStep();
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IupApp::_iupClose(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IupClose();
	args.GetReturnValue().Set(Undefined(isolate));
}

}

int main(int argc,char** argv)
{
	return 0;
}