
	adcloud_sdk_nodejs �Ƕ�Ӧ��nodejsƽ̨ͨѶ�⣬ʹ��ʱ�ŵ�node_modules��
	
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
		appid:�ַ������ͣ�Ϊ�����Ӧ�ñ�ţ����� "app_demo"
		icsAddr:�������ͣ���ͨѶ�ķ�������ַ��Ĭ��Ϊ ["service.ics.aodianyun.com:8365"]
		apppwd:�ַ������ͣ�Ϊ�����Ӧ�����룬���� "app123456"
		
	App method
		app.Start() 
		app�����󣬵������start��ʽ�������񣬲���Ҫ������ֱ�ӵ��þ���
		
		app.Stop()
		�� app.Start ��Ӧ����ֹͣ����,����Ҫ����
		
		app.CloseClient( id )
		�ر�ĳһָ�����ӣ�idΪ���ӱ�ʾ��
		
		app.SendToClient( id )
		��һָ�������ӣ��������ݣ�idΪ���ӱ�ʾ��
		
		app.AddScope(scope,id)
		scope:�ַ������ͣ�����ǿ��ַ���
		id:���ӱ�ʾ��
		�� ����id ���� scope��Ⱥ������		���Ǹ��ܺõĹ��ܣ�ͨ������Ⱥ���򣬿���ʹ��Ⱥ���������������ݷ���Ч�ʣ�����Ⱥ��������1������ӣ�Ⱥ��ֻҪ����һ�Σ�������������Ҫ1��Σ���
		
		app.DelScope(scope,id)
		������id��scope����ɾ�������ӶϿ�ʱ��Ĭ�ϴ������Ѿ����������ɾ�����ýӿ���Ҫ���������������˳�
		
		app.SendToScope(scope, pkt )
		Ⱥ������scope��Ⱥ��pkt���ģ�pkt���Ŀ����� ��������ַ���
		�Ƽ���ʹ�øýӿڣ�����������Ӧ�õ����緢��Ч��
		
		app.BroadCast(pkt)
		�ڱ�Ӧ���ڹ㲥���ݰ���ֻҪ�Ǳ�Ӧ�õ����Ӷ����յ������Ⱥ����һ���Ż��ӿ�
		
		app.SendToOtherApp(appid,pkt)
		appid:�ַ������ͣ�Ŀ��Ӧ�ñ�ţ�����ǰ����֪���Է��ı��
		pkt:�ַ������߶���
		�������ж��Ӧ�ã����ڶ�Ӧ��֮�佻�����ݣ�����ӿڿ������㻥ͨ����
		
	App event:
		app.on('open',function ())
		app.Start ������ɹ������������ӣ�����յ������Ϣ����ʾ���ӳɹ�
		
		app.on('close',function(err))
		���Ӧ��������ΪǷ�ѡ����������жϡ���ͨѶƽ̨���ϵ�ԭ��Ͽ���������յ�����Ϣ
		err���ַ������ͣ��Ա��ζϿ�ԭ�������
		�����������app.Stop �򲻻��յ�����Ϣ
		
		app.on("client_in",function(id,addr))
		���ͻ��˽������ӳɹ��󣬻��յ������Ϣ
		id:�ͻ������ӱ�ʾ
		addr:�ͻ������ӵ�����ip��˿�port
		
		app.on("client_data",function(id,buf))
		���ͻ�����Ӧ�÷�������ʱ�����������յ�
		id:�ͻ������ӱ�ʾ��
		buf:Buffer���ͣ����Ը��ݿͻ��˴��ݵĸ�ʽ��ת������Ӧ�ĸ�ʽ���д���
		
		app.on("client_out",function(id) )
		���ͻ������ӹر�ʱ�����յ������Ϣ
		id:�ͻ������ӱ�ʾ��
		
		app.on("app_data",function(appid,buf))
		���յ�����Ӧ�÷�����������ʱ����������Ϣ
		appid:���ͷ���Ӧ�ñ��
		buf:Buffer ���ͣ������ͷ����͵ĸ�ʽ��ת������Ӧ�ĸ�ʽ���д���