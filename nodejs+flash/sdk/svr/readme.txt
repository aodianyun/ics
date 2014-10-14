
	adcloud_sdk_nodejs 是对应的nodejs平台通讯库，使用时放到node_modules内
	
	Create
		require
		
	App method
		Start
		Stop
		CloseClient
		SendToClient
		AddScope
		DelScope
		SendToScope
		BroadCast
		SendToOtherApp
	App event
		open
		close
		client_in
		client_data
		client_out
		app_data
		

	Create 
		require("adcloud_sdk_nodejs").App.Create( appid,icsAddr,apppwd);
		appid:字符串类型，为申请的应用编号，例如 "app_demo"
		icsAddr:数组类型，云通讯的服务器地址，默认为 ["service.ics.aodianyun.com:8365"]
		apppwd:字符串类型，为申请的应用密码，例如 "app123456"
		
	App method
		app.Start() 
		app创建后，调用这个start正式启动服务，不需要参数，直接调用就行
		
		app.Stop()
		与 app.Start 对应，来停止服务,不需要参数
		
		app.CloseClient( id )
		关闭某一指定连接，id为连接标示符
		
		app.SendToClient( id )
		向一指定的连接，发送数据，id为连接标示符
		
		app.AddScope(scope,id)
		scope:字符串类型，任意非空字符串
		id:连接标示符
		将 连接id 加入 scope的群发集合		这是个很好的功能，通过加入群发域，可以使用群发，极大的提高数据发送效率，假设群发域内有1万个连接，群发只要发送一次，遍历发送则需要1万次！！
		
		app.DelScope(scope,id)
		将连接id从scope域中删除，连接断开时会默认从所有已经加入的域中删除，该接口主要用于主动从域中退出
		
		app.SendToScope(scope, pkt )
		群发！向scope域群发pkt报文，pkt报文可以是 对象或者字符串
		推荐多使用该接口，可以提升本应用的网络发送效率
		
		app.BroadCast(pkt)
		在本应用内广播数据包，只要是本应用的连接都会收到，针对群发的一个优化接口
		
		app.SendToOtherApp(appid,pkt)
		appid:字符串类型，目标应用编号，发送前必须知道对方的编号
		pkt:字符串或者对象
		假如你有多个应用，想在多应用之间交换数据，这个接口可以让你互通数据
		
	App event:
		app.on('open',function ())
		app.Start 后，如果成功建立服务连接，则会收到这个消息，表示连接成功
		
		app.on('close',function(err))
		如果应用连接因为欠费、本地网络中断、云通讯平台故障等原因断开服务，则会收到该消息
		err：字符串类型，对本次断开原因的描述
		如果主动调用app.Stop 则不会收到本消息
		
		app.on("client_in",function(id,addr))
		当客户端建立连接成功后，会收到这个消息
		id:客户端连接标示
		addr:客户端连接的网络ip与端口port
		
		app.on("client_data",function(id,buf))
		当客户端向应用发送数据时，会在这里收到
		id:客户端连接标示符
		buf:Buffer类型，可以根据客户端传递的格式，转换成相应的格式进行处理
		
		app.on("client_out",function(id) )
		当客户端连接关闭时，会收到这个消息
		id:客户端连接标示符
		
		app.on("app_data",function(appid,buf))
		当收到其他应用发送来的数据时，触发本消息
		appid:发送方的应用标号
		buf:Buffer 类型，按发送方发送的格式，转换成相应的格式进行处理