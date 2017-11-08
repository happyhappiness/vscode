char *client_name(int fd)
{
	struct sockaddr sa;
	struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
	int     length = sizeof(sa);
	static char name_buf[100];
	struct hostent *hp;
	char **p;
	char *def = "UNKNOWN";

	strcpy(name_buf,def);

	if (getpeername(fd, &sa, &length)) {
		exit_cleanup(1);
	}

	/* Look up the remote host name. */
	if ((hp = gethostbyaddr((char *) &sockin->sin_addr,
				sizeof(sockin->sin_addr),
				AF_INET))) {
		strlcpy(name_buf,(char *)hp->h_name,sizeof(name_buf) - 1);
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