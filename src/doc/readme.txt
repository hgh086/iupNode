1. 编译方式
    编译运行环境：VS2013，nodejs v4.2.1，Iup v3.16, im 3.10, cd 5.9
    运行b.bat

2. 使用方式
    总共CoreObject、IupApp、IDialog、ILabel、IButton、IText、IMultiLine、IList、IComboBox、ITree、IImage、ICanvas、IBitmap几个基类。

2.1 继承方式
	javascript采用 extend的继承方法。例如
	var MyDialog = iup.IDialog.extend({
		init: function() {this._super()},
		example: function() {}
	})
2.2 CoreObject的使用方法。
    为可继承公共基类，不建议直接使用。

2.3 IupApp的使用方法。
    iupOpen 初始化IUP
    run 运行消息主循环
    single 运行单步消息循环，配合setInterval使用可实现与nodejs/iojs的异步兼容。见样例。
    iupClose 关闭IUP
	
2.4 IDialog的使用方法。
    init 构造函数, init(w,h,control1,control2,control3,...)
	show 显示对话框
	setTitle 设置标题文字, setTitle(txt)
	setCloseCB 设置关闭事件回调函数, setCloseCB(func), func()
	setResizeCB 设置大小变化事件回调函数, setResizeCB(func), func(w,h)
	setShowCB 设置显示事件回调函数, setShowCB(func), func(stat)
	setButtonActionCB 设置按钮点击事件回调函数, setButtonActionCB(control,func), func()
	setTextValueChangedCB 设置文本框变化事件回调函数, setTextValueChangedCB(control,func), func()
	setListDblClickCB 设置列表框双击事件回调函数, setListDblClickCB(control,func), func(item,text)
	setListValueChangedCB 设置列表框变化事件回调函数, setListValueChangedCB(control,func), func()
	setTreeSelectionCB 设置树形控件选择变化事件回调函数, setTreeSelectionCB(control,func), func(id,stat)
	setTreeExecuteLeafCB 设置树形控件叶子节点双击事件回调函数, setTreeExecuteLeafCB(control,func), func(id)
	redraw 重画指令
	destroy 销毁对话框

2.5 ILabel的使用方法。
	init 构造函数, init(title,x,y)
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setTitle 设置标题文字, setTitle(title)
	setImage 设置图片, setImage(name), 参数name在IImage中设置

2.6 IButton的使用方法。
	init 构造函数, init(title,x,y,w,h)
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	setTitle 设置标题文字, setTitle(title)
	setImage 设置图片, setImage(name), 参数name在IImage中设置
	
2.7 IText的使用方法。
	init 构造函数, init(x,y,w,h,readonly), readonly=1 只读
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	setValue 设置文本值, setValue(txt)
	getValue 获取本本值, getValue(), 返回文本值
	appendText 添加文本值, appendText(txt)

2.8 IMultiLine的使用方法。
	init 构造函数, init(x,y,w,h,readonly), readonly=1 只读
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	setValue 设置文本值, setValue(txt)
	getValue 获取文本值, getValue(), 返回文本值
	appendText 添加文本值, appendText(txt)

2.9 IList的使用方法。
	init 构造函数, init(x,y,w,h)
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	getValue 获取选中的选项, getValue(), 返回数字
	appendItem 添加选项, appendItem(txt)
	removeItem 删除选项, removeItem(index), index<1 删除所有选项
	getCount 获取选项数量, getCount(), 返回数字
	getItemString 根据编号获取选项文本, getItemString(index)

2.10 IComboBox的使用方法。
	init 构造函数, init(x,y,w,h)
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	getValue 获取选中的选项, getValue(), 返回数字
	appendItem 添加选项, appendItem(txt)
	removeItem 删除选项, removeItem(index), index<1 删除所有选项
	getCount 获取选项数量, getCount(), 返回数字
	getItemString 根据编号获取选项文本, getItemString(index)

2.11 ITree的使用方法。
	init 构造函数, init(x,y,w,h)
	setPosx 设置x位置, setPosx(x)
	setPosy 设置y位置, setPosy(y)
	setSize 设置大小, setSize(w,h)
	setNodeText 设置节点文本, setNodeText(id,text)
	getNodeText 获取节点文本, getNodeText(id), 返回文本值
	getNodeChildCount 获取节点的子节点数目, getNodeChildCount(id), 返回数字
	getNodeDepth 获取节点的深度, getNodeDepth(id), 返回数字
	getNodeParent 获取父节点ID, getNodeParent(id), 返回数字
	getNodeKind 获取节点类型, getNodeKind(id), "LEAF" 或 "BRANCH"
	addBranch 添加树干节点, addBranch(id,text)
	addLeaf 添加叶子节点, addLeaf(id,text)
	insertBranch 插入树干节点, insertBranch(id,text)
	insertLeaf 插入叶子节点, insertLeaf(id,text)
	delNode 删除节点及子节点, delNode(id)
	getNodeCount 获取节点总数, getNodeCount(), 返回数字
	getSelection 获取选中节点的ID, getSelection(), 返回数字
	getLastAdd 获取最后添加的节点ID，getSelection(), 返回数字

2.12 IImage的使用方法。
	init 构造函数, init(filepath)
	destroy 销毁图片, destroy()
	setImageName 设置图片名称, setImageName(name)
	getChannels 获取图片颜色通道数, getChannels(), 返回数字
	getWidth 获取图片宽度, getWidth(), 返回数字
	getHeight 获取图片高度, getHeight(), 返回数字

2.13 ICanvas的使用方法。
	init 构造函数, init(x,y,w,h)
	createCDCanvas 新建画布, createCDCanvas(), 必须在show之后调用
	clear 以背景色清楚画面, clear()
	foreground 设置前景色, foreground(r,g,b)
	background 设置背景色, background(r,g,b)
	lineStyle 设置线样式, lineStyle(st), st=0连续 1 虚线 2点 3虚线点 4虚线点点
	lineWidth 设置线宽度, lineWidth(w)
	line 画线, line(x1,y1,x2,y2)
	rect 画长方形, rect(xmin,xmax,ymin,ymax)
	arc 画弧线, arc(xc,yc,w,h,angle1,angle2)
	box 填充长方形, box(xmin,xmax,ymin,ymax)
	sector 填充弧线, sector(xc,yc,w,h,angle1,angle2)
	chord 填充弧线, chord(xc,yc,w,h,angle1,angle2)
	font 设置字体, font(face,style,size), style=1正常 2粗体 3斜体 4下划线 5中划线, 只设置大小样例 font("",-1,size)
	text 画文字, text(x,y,text)
	putBitmap 画图片, putBitmap(bitmap,x,y,w,h)
	setDrawCB 设置重画回调函数, setDrawCB(func), func(posx,posy)
	setMotionCB 设置鼠标移动回调函数, setMotionCB(func), func(x,y)
	setKeyPressCB 设置键盘输入回调函数, setKeyPressCB(func), func(c)
	redraw 重画指令, redraw()
	destroy 销毁画布, destroy()

2.14 IBitmap的使用方法。
	init 构造函数, init()
	createBitmap 装载文件, createBitmap(filepath)
	getChannels 获取图片颜色通道数, getChannels(), 返回数字
	getWidth 获取图片宽度, getWidth(), 返回数字
	getHeight 获取图片高度, getHeight(), 返回数字	
	destroy 销毁图片, destroy()

2.15 IFileDlg的使用方法。
	init 构造函数, init(type,title,filter), type=0打开 1保存 2目录
	popup 显示对话框, popup()
	getValue 获取返回值,getValue()
	destroy 销毁对话框,destroy()

2.16 IMessageDlg的使用方法。
	init 构造函数, init(type,title,message), type=0确认 1确认取消 2是否
	popup 显示对话框, popup()
	getValue 获取返回值,getValue()
	destroy 销毁对话框,destroy()

3 使用举例
3.1 普通样例
/*test.js****************************/
var iup = require('iupnode');

var theApp = new iup.IupApp();
theApp.iupOpen();

var MyCanvas = iup.ICanvas.extend({
	init: function(x,y,w,h) {
		this._super(x,y,w,h);
		this.bmp1 = new iup.IBitmap();
		this.bmp1.createBitmap("beauty.jpg");
		this.setDrawCB(this.ondraw);
	},
	ondraw: function(posx,posy) {
		this.clear();
		this.foreground(255,0,0);
		this.lineWidth(2);
		this.line(10,10,100,100);
		this.rect(10,100,10,100);
		this.arc(200,80,100,50,0,270);
		this.foreground(0,0,255);
		this.box(10,100,110,200);
		this.chord(200,180,100,50,0,270);
		this.text(10,250,"hello world 语文");
		this.putBitmap(this.bmp1,300,280,200,-240);
	}
})

var MyDialog = iup.IDialog.extend ({
	init: function(w,h) {
		this.lb1 = new iup.ILabel("label 1",20,50);
		this.btn1 = new iup.IButton("press",100,20,100,30);
		this.btn2 = new iup.IButton("me",100,60,100,30);
		this.txt1 = new iup.IText(250,50,200,30);
		this.ml1 = new iup.IMultiLine(20,100,700,150,1);
		this.lst = new iup.IList(20,280,150,100);
		this.cb1 = new iup.IComboBox(550,50,100,30);
		this.tr1 = new iup.ITree(20,400,150,180);
		this.cv1 = new MyCanvas(200,280,550,300);
		this._super(w,h,this.lb1,this.btn1,this.btn2,this.txt1,this.ml1,this.lst,this.cb1,this.tr1,this.cv1);
		this.show();
		this.cv1.createCDCanvas();
		this.setResizeCB(this.onSize);
		this.setButtonActionCB(this.btn1,this.onbtnclick);
		this.setButtonActionCB(this.btn2,this.onbtnclick2);
		this.setListDblClickCB(this.lst,this.onlstdblclick);
		this.setListValueChangedCB(this.lst,this.onlstchande);
		this.setTitle("test");
		this.lst.appendItem("11111");
		this.lst.appendItem("22222");
		this.lst.appendItem("33333");
		this.lst.appendItem("44444");
		this.lst.appendItem("55555");
		this.lst.appendItem("66666");
		this.lst.appendItem("77777");
		this.lst.appendItem("88888");
		this.tr1.setNodeText(0,"Root");
		this.tr1.addBranch(0,"Man");
		this.tr1.addLeaf(1,"Jackie");
		this.tr1.insertLeaf(2,"Tommy");
		this.tr1.insertBranch(1,"Woman");
		this.tr1.addLeaf(4,"Rose");
		this.tr1.addLeaf(4,"Alice");
		this.tr1.addLeaf(5,"Kitty");
		this.setTreeExecuteLeafCB(this.tr1,this.ontreesel);
		this.redraw();
	},
	onSize: function(w,h){
		this.ml1.appendText("size chande w = " + w + ", h = " + h);
	},
	onbtnclick: function() {
		this.ml1.appendText("btn1 click");
		var n = this.tr1.getSelection();
		this.ml1.appendText("child = " + this.tr1.getNodeChildCount(n));
	},
	onbtnclick2: function() {
		this.ml1.appendText("btn2 click");
		this.ml1.appendText("lst value" + this.lst.getValue());
	},
	onlstdblclick: function(item,txt) {
		this.ml1.appendText("list dbl click " + item + " - " + txt);
	},
	onlstchande: function() {
		console.log("list change");
	},
	ontreesel: function(id) {
		console.log("sel text =" + this.tr1.getNodeText(id) );
		console.log("sel depth =" + this.tr1.getNodeDepth(id) );
		console.log("sel parent =" + this.tr1.getNodeParent(id) );
		console.log("sel kind =" + this.tr1.getNodeKind(id) );
	}
})

var dlg = new MyDialog(800,600);

theApp.run();
dlg.destroy();
theApp.iupClose();

/************************************/

3.2 异步兼容样例
/*async.js***************************/
var iup = require('iupnode');
var fs = require('fs');

var theApp = new iup.IupApp();
theApp.iupOpen();

var MyDialog = iup.IDialog.extend ({
	init: function(w,h) {
		this.btn1 = new iup.IButton("Quit",20,20,100,30);
		this.btn2 = new iup.IButton("Load",150,20,100,30);
		this.ml1 = new iup.IMultiLine(20,60,600,400);
		this._super(w,h,this.btn1,this.btn2,this.ml1);
		this.show();
		this.setButtonActionCB(this.btn1,this.onbtnclick1);
		this.setButtonActionCB(this.btn2,this.onbtnclick2);		
	},
	onbtnclick1: function() {
		process.exit();
	},
	onbtnclick2: function() {
		fs.readFile("async.js", function(err,data) {
			if (err) throw err;
			dlg.ml1.appendText(data.toString("utf8"));
		})
	}
})

var dlg = new MyDialog(640,480);

var vvv = setInterval( function() {
	var r = theApp.single();
	if (r == -3) {
		dlg.destroy();
		clearInterval(vvv);
		theApp.iupClose();
		console.log("fin");
	}
},1);
/************************************/

