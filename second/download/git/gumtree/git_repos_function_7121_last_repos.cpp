static void read_credential(void)
{
	char buf[1024];

	while (fgets(buf, sizeof(buf), stdin)) {
		char *v;
		int len = strlen(buf);
		/* strip trailing CR / LF */
		while (len && strchr("\r\n", buf[len - 1]))
			buf[--len] = 0;

		if (!*buf)
			break;

		v = strchr(buf, '=');
		if (!v)
			die("bad input: %s", buf);
		*v++ = '\0';

		if (!strcmp(buf, "protocol"))
			protocol = utf8_to_utf16_dup(v);
		else if (!strcmp(buf, "host"))
			host = utf8_to_utf16_dup(v);
		else if (!strcmp(buf, "path"))
			path = utf8_to_utf16_dup(v);
		else if (!strcmp(buf, "username")) {
			wusername = utf8_to_utf16_dup(v);
		} else if (!strcmp(buf, "password"))
			password = utf8_to_utf16_dup(v);
		else
			die("unrecognized input");
	}
}