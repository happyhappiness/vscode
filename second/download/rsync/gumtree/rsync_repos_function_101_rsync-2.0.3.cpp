char *client_name(int fd)
{
	struct sockaddr sa;
	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
	int     length = sizeof(sa);
	static char name_buf[100];
	struct hostent *hp;

	strcpy(name_buf,"UNKNOWN");

	if (getpeername(fd, &sa, &length)) {
		exit(1);
	}

	/* Look up the remote host name. */
	if ((hp = gethostbyaddr((char *) &sockin->sin_addr,
				sizeof(sockin->sin_addr),
				AF_INET))) {
		strlcpy(name_buf,(char *)hp->h_name,sizeof(name_buf) - 1);
	}

	return name_buf;
}