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
	if (start_command(&child)) {
		logerror("daemon access hook '%s' failed to start",
			 access_hook);
		goto error_return;
	}
	if (strbuf_read(&buf, child.out, 0) < 0) {
		logerror("failed to read from pipe to daemon access hook '%s'",
			 access_hook);
		strbuf_reset(&buf);
		seen_errors = 1;
	}
	if (close(child.out) < 0) {
		logerror("failed to close pipe to daemon access hook '%s'",
			 access_hook);
		seen_errors = 1;
	}
	if (finish_command(&child))
		seen_errors = 1;

	if (!seen_errors) {
		strbuf_release(&buf);
		return 0;
	}

error_return:
	strbuf_ltrim(&buf);
	if (!buf.len)
		strbuf_addstr(&buf, "service rejected");
	eol = strchr(buf.buf, '\n');
	if (eol)
		*eol = '\0';
	errno = EACCES;
	daemon_error(dir, buf.buf);
	strbuf_release(&buf);
	return -1;
}