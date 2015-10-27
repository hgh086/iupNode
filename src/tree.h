#ifndef IUP_TREE_H
#define IUP_TREE_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class ITree : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	ITree();
	~ITree();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosx(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosy(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setSize(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setNodeText(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeText(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeChildCount(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeDepth(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeParent(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeKind(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _addBranch(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _addLeaf(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _insertBranch(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _insertLeaf(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _delNode(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getNodeCount(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getSelection(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getLastAdd(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
