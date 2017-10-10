			return;
		}
	}
	die("No such service %s", name);
}

static char *xstrdup_tolower(const char *str)
{
	char *p, *dup = xstrdup(str);
	for (p = dup; *p; p++)
		*p = tolower(*p);
	return dup;
}

static void parse_host_and_port(char *hostport, char **host,
	char **port)
{
	if (*hostport == '[') {
		char *end;

