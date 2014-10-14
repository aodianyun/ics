

//º”‘ÿ‘∆Õ®—∂ø‚
var app_mod = require("adcloud_sdk_nodejs").App;
var config = require("./config");

var app = app_mod.Create(config.appid,config.proxy_addrs,config.apppwd);

var mgr_moudle_path = "./server/logic";

var mod_manager = require(mgr_moudle_path);

var mod = null;

// emit when open sucess£°
app.on('open',function(){
	console.log("app start sucess!");
	mod = mod_manager.Create(app);
})

//emit when a new client connect in
app.on("client_in",function(id,addr){
	mod.OnClientIn(id,addr);
})

// emit when recieve data from a client
app.on("client_data",function(id,buf){	
	mod.OnClientData(id,JSON.parse( buf.toString() ));
})

//emit when client end connection
app.on("client_out",function(id){
	mod.OnClientOut(id);
})

// emit when recieve from other app
app.on("app_data",function(appid,buf){
	mod.OnOhterAppData(appid,buf)
})

// emit when app stop connetion with adcloud
app.on('close',function(err){
	console.log("close",err);
	if(mod && mod.Release)
		mod.Release();
	setTimeout(ReStart,3000);
})

app.Start();

function ReStart(){
	var childprocess = require('child_process');
	var arr = [];
	for(var i = 2;i<process.argv.length;i++){
		arr.push(process.argv[i]);
	}
	childprocess.fork(__filename,arr);
	process.exit();
}
process.on('uncaughtException', function (err) {
	console.log('Caught exception: ' ,err,err.stack);
});