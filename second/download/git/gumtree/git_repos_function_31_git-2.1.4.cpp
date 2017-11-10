struct child_process *git_connect(int fd[2], const char *url,
				  const char *prog, int flags)
{
	char *hostandport, *path;
	struct child_process *conn = &no_fork;
	enum protocol protocol;
	struct strbuf cmd = STRBUF_INIT;

	/* Without this we cannot rely on waitpid() to tell
	 * what happened to our children.
	 */
	signal(SIGCHLD, SIG_DFL);

	protocol = parse_connect_url(url, &hostandport, &path);
	if (flags & CONNECT_DIAG_URL) {
		printf("Diag: url=%s\n", url ? url : "NULL");
		printf("Diag: protocol=%s\n", prot_name(protocol));
		printf("Diag: hostandport=%s\n", hostandport ? hostandport : "NULL");
		printf("Diag: path=%s\n", path ? path : "NULL");
		conn = NULL;
	} else if (protocol == PROTO_GIT) {
		/* These underlying connection commands die() if they
		 * cannot connect.
		 */
		char *target_host = xstrdup(hostandport);
		if (git_use_proxy(hostandport))
			conn = git_proxy_connect(fd, hostandport);
		else
			git_tcp_connect(fd, hostandport, flags);
		/*
		 * Separate original protocol components prog and path
		 * from extended host header with a NUL byte.
		 *
		 * Note: Do not add any other headers here!  Doing so
		 * will cause older git-daemon servers to crash.
		 */
		packet_write(fd[1],
			     "%s %s%chost=%s%c",
			     prog, path, 0,
			     target_host, 0);
		free(target_host);
	} else {
		conn = xcalloc(1, sizeof(*conn));

		strbuf_addstr(&cmd, prog);
		strbuf_addch(&cmd, ' ');
		sq_quote_buf(&cmd, path);

		conn->in = conn->out = -1;
		if (protocol == PROTO_SSH) {
			const char *ssh = getenv("GIT_SSH");
			int putty = ssh && strcasestr(ssh, "plink");
			char *ssh_host = hostandport;
			const char *port = NULL;
			get_host_and_port(&ssh_host, &port);
			port = get_port_numeric(port);

			if (!ssh) ssh = "ssh";

			argv_array_push(&conn->args, ssh);
			if (putty && !strcasestr(ssh, "tortoiseplink"))
				argv_array_push(&conn->args, "-batch");
			if (port) {
				/* P is for PuTTY, p is for OpenSSH */
				argv_array_push(&conn->args, putty ? "-P" : "-p");
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			/* remove repo-local variables from the environment */
			conn->env = local_repo_env;
			conn->use_shell = 1;
		}
		argv_array_push(&conn->args, cmd.buf);

		if (start_command(conn))
			die("unable to fork");

		fd[0] = conn->out; /* read from child's stdout */
		fd[1] = conn->in;  /* write to child's stdin */
		strbuf_release(&cmd);
	}
	free(hostandport);
	free(path);
	return conn;
}