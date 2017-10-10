			return;
		}
	}
	die("No such service %s", name);
}

static void parse_host_and_port(char *hostport, char **host,
	char **port)
{
	if (*hostport == '[') {
		char *end;

