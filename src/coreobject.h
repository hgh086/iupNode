#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include <node.h>
#include <node_object_wrap.h>
#include <iup.h>

namespace iupnode {
	
class CoreObject : public node::ObjectWrap {
public:
	static void Init(v8::Local<v8::Object> exports);
	
	Ihandle* hwnd;

protected:
	CoreObject();
	~CoreObject();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void extend(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void extendCallHandler(const v8::FunctionCallbackInfo<v8::Value>& args);
		
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);

	static v8::Persistent<v8::Function> constructor;
	static int bInit;
};

}

#endif