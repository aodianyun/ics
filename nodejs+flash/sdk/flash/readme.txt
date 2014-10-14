
	加载链接 adcloud_client.swc
	
	连接创建与回调
		function AdCloudClient(arr:Vector.<String>,appid:String,lis:AdCloudClientListener)
		function Open():void
		function OnOpen():void
		function OnClose(err:String):void
		function OnMessage(bytes:ByteArray):void
		function OnOpenFail(err:String):void
	
	连接接口
		function Send(bytes:ByteArray):Boolean
		function Close():void
		
	
	
	连接创建
		function AdCloudClient(arr:Vector.<String>,appid:String,lis:AdCloudClientListener)
		function Open():void
		例如：
			var cli_:AdCloudClient = new AdCloudClient(["service.ics.aodianyun.com:8365"],"app_demo",this);
			cli_.Open();
		如上，就完成了连接请求
	
		function OnOpen():void
		当发起Open时，如果成功，收到此消息
		
		function OnOpenFail(err:String):void
		当发起Open时，如果失败，收到此消息
		
		function OnClose(err:String):void
		当连接非主动关闭时触发，err 是关闭原因描述
		
		function OnMessage(bytes:ByteArray):void
		当收到服务器端数据时触发
		
	
	连接接口：
		function Send(bytes:ByteArray):Boolean
		发送数据到服务器
		
		function Close():void
		主动关闭连接