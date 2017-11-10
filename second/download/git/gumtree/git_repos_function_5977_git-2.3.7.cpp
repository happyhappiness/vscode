static void read_credential(void)
{
	char buf[1024];

	while (fgets(buf, sizeof(buf), stdin)) {
		char *v;

		if (!strcmp(buf, "\n"))
			break;
		buf[strlen(buf)-1] = '\0';

		v = strchr(buf, '=');
		if (!v)
			die("bad input: %s", buf);
		*v++ = '\0';

		if (!strcmp(buf, "protocol")) {
			if (!strcmp(v, "imap"))
				protocol = kSecProtocolTypeIMAP;
			else if (!strcmp(v, "imaps"))
				protocol = kSecProtocolTypeIMAPS;
			else if (!strcmp(v, "ftp"))
				protocol = kSecProtocolTypeFTP;
			else if (!strcmp(v, "ftps"))
				protocol = kSecProtocolTypeFTPS;
			else if (!strcmp(v, "https"))
				protocol = kSecProtocolTypeHTTPS;
			else if (!strcmp(v, "http"))
				protocol = kSecProtocolTypeHTTP;
			else if (!strcmp(v, "smtp"))
				protocol = kSecProtocolTypeSMTP;
			else /* we don't yet handle other protocols */
				exit(0);
		}
		else if (!strcmp(buf, "host")) {
			char *colon = strchr(v, ':');
			if (colon) {
				*colon++ = '\0';
				port = atoi(colon);
			}
			host = xstrdup(v);
		}
		else if (!strcmp(buf, "path"))
			path = xstrdup(v);
		else if (!strcmp(buf, "username"))
			username = xstrdup(v);
		else if (!strcmp(buf, "password"))
			password = xstrdup(v);
	}
}