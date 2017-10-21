	for (i=0;i<3;i++) {
		close(i); 
		open("/dev/null", O_RDWR);
	}
}

/*******************************************************************
 return the IP addr of the client as a string 
 ******************************************************************/
char *client_addr(int fd)
{
	struct sockaddr sa;
	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
	int     length = sizeof(sa);
	static char addr_buf[100];
	static int initialised;

	if (initialised) return addr_buf;

	initialised = 1;

	if (getpeername(fd, &sa, &length)) {
		exit_cleanup(RERR_SOCKETIO);
	}
	
	strlcpy(addr_buf,(char *)inet_ntoa(sockin->sin_addr), sizeof(addr_buf));
	return addr_buf;
}


/*******************************************************************
 return the DNS name of the client 
 ******************************************************************/
char *client_name(int fd)
{
	struct sockaddr sa;
	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
	int     length = sizeof(sa);
	static char name_buf[100];
	struct hostent *hp;
	char **p;
	char *def = "UNKNOWN";
	static int initialised;

	if (initialised) return name_buf;

	initialised = 1;

	strcpy(name_buf,def);

	if (getpeername(fd, &sa, &length)) {
		exit_cleanup(RERR_SOCKETIO);
	}

	/* Look up the remote host name. */
	if ((hp = gethostbyaddr((char *) &sockin->sin_addr,
				sizeof(sockin->sin_addr),
				AF_INET))) {
		strlcpy(name_buf,(char *)hp->h_name,sizeof(name_buf));
	}


	/* do a forward lookup as well to prevent spoofing */
	hp = gethostbyname(name_buf);
	if (!hp) {
		strcpy(name_buf,def);
		rprintf(FERROR,"reverse name lookup failed\n");
	} else {
		for (p=hp->h_addr_list;*p;p++) {
			if (memcmp(*p, &sockin->sin_addr, hp->h_length) == 0) {
				break;
			}
		}
		if (!*p) {
			strcpy(name_buf,def);
			rprintf(FERROR,"reverse name lookup mismatch - spoofed address?\n");
		} 
	}

	return name_buf;
}

/*******************************************************************
convert a string to an IP address. The string can be a name or
dotted decimal number
  ******************************************************************/
struct in_addr *ip_address(const char *str)
{
	static struct in_addr ret;
	struct hostent *hp;

	/* try as an IP address */
	if (inet_aton(str, &ret) != 0) {
		return &ret;
	}

	/* otherwise assume it's a network name of some sort and use 
	   gethostbyname */
	if ((hp = gethostbyname(str)) == 0) {
		rprintf(FERROR, "gethostbyname: Unknown host. %s\n",str);
		return NULL;
	}

	if (hp->h_addr == NULL) {
		rprintf(FERROR, "gethostbyname: host address is invalid for host %s\n",str);
		return NULL;
	}

	if (hp->h_length > sizeof(ret)) {
		rprintf(FERROR, "gethostbyname: host address is too large\n");
		return NULL;
	}

	memcpy(&ret.s_addr, hp->h_addr, hp->h_length);

	return(&ret);
}
