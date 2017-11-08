static int open_socket_in(int type, int port)
{
	struct hostent *hp;
	struct sockaddr_in sock;
	char host_name[200];
	int res;
	int one=1;

	/* get my host name */
	if (gethostname(host_name, sizeof(host_name)) == -1) { 
		rprintf(FERROR,"gethostname failed\n"); 
		return -1; 
	} 

	/* get host info */
	if ((hp = gethostbyname(host_name)) == 0) {
		rprintf(FERROR,"gethostbyname: Unknown host %s\n",host_name);
		return -1;
	}
  
	bzero((char *)&sock,sizeof(sock));
	memcpy((char *)&sock.sin_addr,(char *)hp->h_addr, hp->h_length);
	sock.sin_port = htons(port);
	sock.sin_family = hp->h_addrtype;
	sock.sin_addr.s_addr = INADDR_ANY;
	res = socket(hp->h_addrtype, type, 0);
	if (res == -1) { 
		rprintf(FERROR,"socket failed\n"); 
		return -1; 
	}

	setsockopt(res,SOL_SOCKET,SO_REUSEADDR,(char *)&one,sizeof(one));

	/* now we've got a socket - we need to bind it */
	if (bind(res, (struct sockaddr * ) &sock,sizeof(sock)) == -1) { 
		rprintf(FERROR,"bind failed on port %d\n", port);
		close(res); 
		return -1;
	}

	return res;
}