		return PROTO_SSH;
	if (!strcmp(name, "file"))
		return PROTO_FILE;
	die("I don't handle protocol '%s'", name);
}

#define STR_(s)	# s
#define STR(s)	STR_(s)

static void get_host_and_port(char **host, const char **port)
{
	char *colon, *end;

	if (*host[0] == '[') {
		end = strchr(*host + 1, ']');
		if (end) {
			*end = 0;
			end++;
			(*host)++;
		} else
			end = *host;
	} else
		end = *host;
	colon = strchr(end, ':');

	if (colon) {
		*colon = 0;
		*port = colon + 1;
	}
}

static void enable_keepalive(int sockfd)
{
	int ka = 1;
