static int establish_proxy_connection(int fd, char *host, int port)
{
	char buffer[1024];
	char *cp;

	snprintf(buffer, sizeof(buffer), "CONNECT %s:%d HTTP/1.0\r\n\r\n", host, port);
	if (write(fd, buffer, strlen(buffer)) != (int) strlen(buffer)) {
		rprintf(FERROR, "failed to write to proxy: %s\n",
			strerror(errno));
		return -1;
	}

	for (cp = buffer; cp < &buffer[sizeof(buffer) - 1]; cp++) {
		if (read(fd, cp, 1) != 1) {
			rprintf(FERROR, "failed to read from proxy: %s\n",
				strerror(errno));
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
		rprintf(FERROR, "bad response from proxy - %s\n",
			buffer);
		return -1;
	}
	for (cp = &buffer[5]; isdigit(* (unsigned char *) cp) || (*cp == '.'); cp++)
		;
	while (*cp == ' ')
		cp++;
	if (*cp != '2') {
		rprintf(FERROR, "bad response from proxy - %s\n",
			buffer);
		return -1;
	}
	/* throw away the rest of the HTTP header */
	while (1) {
		for (cp = buffer; cp < &buffer[sizeof(buffer) - 1];
		     cp++) {
			if (read(fd, cp, 1) != 1) {
				rprintf(FERROR, "failed to read from proxy: %s\n",
					strerror(errno));
				return -1;
			}
			if (*cp == '\n')
				break;
		}
		if ((cp > buffer) && (*cp == '\n'))
			cp--;
		if ((cp == buffer) && ((*cp == '\n') || (*cp == '\r')))
			break;
	}
	return 0;
}