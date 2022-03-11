  // webbench.cpp : ���ļ����� "socket.c" ������
    /***********************************************************************
       module:       socket.c
       program:      popclient
       SCCS ID:      @(#)socket.c    1.5  4/1/94
       programmer:   Virginia Tech Computing Center
       compiler:     DEC RISC C compiler (Ultrix 4.1)
       environment:  DEC Ultrix 4.3
       description:  UNIX sockets code.
      ***********************************************************************/
    
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <fcntl.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <sys/time.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
      /***********
      ���ܣ�ͨ����ַ�Ͷ˿ڽ�����������
      host:�����ַ
      clientPort:�˿�
      Return��������socket���ӡ�
    		  �������-1����ʾ��������ʧ��
      ************/
    static int Socket(const char *host, int clientPort)
    {
    	int sock;
    	unsigned long inaddr;
    	struct sockaddr_in ad;
    	struct hostent *hp;
    	
    	memset(&ad, 0, sizeof(ad));
    	ad.sin_family = AF_INET;
        
		inaddr = inet_addr(host);/*��inet_addr��������ֵ�ʮ���Ƶ�IPתΪ�޷��ų����Σ�host������www��baifu��comҲ������IP��ַ���ֵĸ�ʽ�����������if�жϡ�
*/
     if (inaddr != INADDR_NONE)
	    // when����Ϊ��ȷ��IP��ַʱ��
     memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    	 else
	   //���host�����������������ַ��������Ǵ���
     {
     hp = gethostbyname(host);//��������ȡIP
    		if (hp == NULL)
    			return -1;
    		memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    	}
    	ad.sin_port = htons(clientPort);
    
    	sock = socket(AF_INET, SOCK_STREAM, 0);
    	if (sock < 0)
    		return sock;
    	//����
    	if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
    		return -1;
    	return sock;
    }


