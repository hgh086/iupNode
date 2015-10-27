#ifndef IUP_APP_H
#define IUP_APP_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {
	
class IupApp : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	
	IupApp();
	~IupApp();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTopWindow(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _iupOpen(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _run(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _single(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _iupClose(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}


#endif