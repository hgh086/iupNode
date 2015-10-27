#ifndef IUP_BUTTON_H
#define IUP_BUTTON_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class IButton : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	IButton();
	~IButton();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosx(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosy(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setSize(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTitle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setImage(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
