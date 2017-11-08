static int establish_proxy_connection(int fd, char *host, int port,
				      char *proxy_user, char *proxy_pass)
{
	char *cp, buffer[1024];
	char *authhdr, authbuf[1024];
	int len;

	if (proxy_user && proxy_pass) {
		stringjoin(buffer, sizeof buffer,
			 proxy_user, ":", proxy_pass, NULL);
		len = strlen(buffer);

		if ((len*8 + 5) / 6 >= (int)sizeof authbuf - 3) {
			rprintf(FERROR,
				"authentication information is too long\n");
			return -1;
		}

		base64_encode(buffer, len, authbuf, 1);
		authhdr = "\r\nProxy-Authorization: Basic ";
	} else {
		*authbuf = '\0';
		authhdr = "";
	}

	snprintf(buffer, sizeof buffer, "CONNECT %s:%d HTTP/1.0%s%s\r\n\r\n",
		 host, port, authhdr, authbuf);
	len = strlen(buffer);
	if (write(fd, buffer, len) != len) {
		rsyserr(FERROR, errno, "failed to write to proxy");
		return -1;
	}

	for (cp = buffer; cp < &buffer[sizeof buffer - 1]; cp++) {
		if (read(fd, cp, 1) != 1) {
			rsyserr(FERROR, errno, "failed to read from proxy");
			return -1;
		}
		if (*cp == '\n')
			break;
	}

	if (*cp != '\n')
		cp++;
	*cp-- = '\0';
	if (*cp == '\r')
		*cp = '\0';
	if (strncmp(buffer, "HTTP/", 5) != 0) {
		rprintf(FERROR, "bad response from proxy -- %s\n",
			buffer);
		return -1;
	}
	for (cp = &buffer[5]; isDigit(cp) || *cp == '.'; cp++) {}
	while (*cp == ' ')
		cp++;
	if (*cp != '2') {
		rprintf(FERROR, "bad response from proxy -- %s\n",
			buffer);
		return -1;
	}
	/* throw away the rest of the HTTP header */
	while (1) {
		for (cp = buffer; cp < &buffer[sizeof buffer - 1]; cp++) {
			if (read(fd, cp, 1) != 1) {
				rsyserr(FERROR, errno,
					"failed to read from proxy");
				return -1;
			}
			if (*cp == '\n')
				break;
		}
		if (cp > buffer && *cp == '\n')
			cp--;
		if (cp == buffer && (*cp == '\n' || *cp == '\r'))
			break;
	}
	return 0;
}