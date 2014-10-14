var config = require("./config");
var child_process = require('child_process');
exports.Check = function(){
	if(config.appid == "demo" || config.appid == ""){
		console.log("请将申请到的应用编号Appid与应用密码Passwd配置到config.js文件中指定位置再启动！");
		child_process.exec("@pause");
		process.exit(1);
	}
}
