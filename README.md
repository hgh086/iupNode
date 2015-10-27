# iupNode
node.js wrapper for iup

The purpose of this tools is write desktop GUI program by nodejs.

Compile Environment: VS2013，nodejs v4.2.1，Iup v3.16, im 3.10, cd 5.9

Build and install:
1. Download nodejs v4.2.1(lib and include),Iup v3.16(static lib and include),im 3.10(static lib and include), cd 5.9(static lib and include). Iup may download in this webside http://webserver2.tecgraf.puc-rio.br/iup/
2. In VS2013 Commandline ru b.bat.
3. copy iupnode.node to node.js node_modules directory.
4.you can use it.

Example:

var iup = require('iupnode');
var fs = require('fs');

var theApp = new iup.IupApp();
theApp.iupOpen();

var MyCanvas = iup.ICanvas.extend({
	init: function(x,y,w,h) {
		this._super(x,y,w,h);
		this.bmp1 = new iup.IBitmap();
		this.bmp1.createBitmap("demo.jpg");
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
		this.text(10,250,"hello world");
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
		var buf = fs.readFileSync("demo.txt");
		this.ml1.appendText("read file demo length =" + buf.length);
		this.ml1.appendText(buf.toString("utf8",0,buf.length));
	},
	onbtnclick2: function() {
		this.ml1.appendText("btn2 click");
		var fdlg = new iup.IFileDlg(0,"slect dir","*.jpg");
		fdlg.popup();
		this.ml1.appendText(fdlg.getValue());
		fdlg.destroy();
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
