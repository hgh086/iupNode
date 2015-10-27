#ifndef IUP_MULTILINE_H
#define IUP_MULTILINE_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class IMultiLine : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	IMultiLine();
	~IMultiLine();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosx(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosy(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setSize(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _appendText(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
