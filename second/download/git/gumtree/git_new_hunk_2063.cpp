	packet_write(1, "ERR %s: %s", msg, dir);
	return -1;
}

static const char *access_hook;

static int run_access_hook(struct daemon_service *service, const char *dir,
			   const char *path, struct hostinfo *hi)
{
	struct child_process child = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	const char *argv[8];
	const char **arg = argv;
	char *eol;
	int seen_errors = 0;

	*arg++ = access_hook;
	*arg++ = service->name;
	*arg++ = path;
	*arg++ = hi->hostname.buf;
	*arg++ = get_canon_hostname(hi);
	*arg++ = get_ip_address(hi);
	*arg++ = hi->tcp_port.buf;
	*arg = NULL;

	child.use_shell = 1;
	child.argv = argv;
	child.no_stdin = 1;
	child.no_stderr = 1;
	child.out = -1;
