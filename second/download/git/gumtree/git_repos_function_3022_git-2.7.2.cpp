static void parse_host_and_port(char *hostport, char **host,
	char **port)
{
	if (*hostport == '[') {
		char *end;

		end = strchr(hostport, ']');
		if (!end)
			die("Invalid request ('[' without ']')");
		*end = '\0';
		*host = hostport + 1;
		if (!end[1])
			*port = NULL;
		else if (end[1] == ':')
			*port = end + 2;
		else
			die("Garbage after end of host part");
	} else {
		*host = hostport;
		*port = strrchr(hostport, ':');
		if (*port) {
			**port = '\0';
			++*port;
		}
	}
}