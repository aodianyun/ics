
	�������� adcloud_client.swc
	
	���Ӵ�����ص�
		function AdCloudClient(arr:Vector.<String>,appid:String,lis:AdCloudClientListener)
		function Open():void
		function OnOpen():void
		function OnClose(err:String):void
		function OnMessage(bytes:ByteArray):void
		function OnOpenFail(err:String):void
	
	���ӽӿ�
		function Send(bytes:ByteArray):Boolean
		function Close():void
		
	
	
	���Ӵ���
		function AdCloudClient(arr:Vector.<String>,appid:String,lis:AdCloudClientListener)
		function Open():void
		���磺
			var cli_:AdCloudClient = new AdCloudClient(["service.ics.aodianyun.com:8365"],"app_demo",this);
			cli_.Open();
		���ϣ����������������
	
		function OnOpen():void
		������Openʱ������ɹ����յ�����Ϣ
		
		function OnOpenFail(err:String):void
		������Openʱ�����ʧ�ܣ��յ�����Ϣ
		
		function OnClose(err:String):void
		�����ӷ������ر�ʱ������err �ǹر�ԭ������
		
		function OnMessage(bytes:ByteArray):void
		���յ�������������ʱ����
		
	
	���ӽӿڣ�
		function Send(bytes:ByteArray):Boolean
		�������ݵ�������
		
		function Close():void
		�����ر�����