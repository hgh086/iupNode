#ifndef IUP_LIST_H
#define IUP_LIST_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class IList : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	IList();
	~IList();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosx(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosy(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setSize(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _appendItem(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _removeItem(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getCount(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getItemString(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
