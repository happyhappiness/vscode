			     target_host, 0);
		free(target_host);
	} else {
		conn = xmalloc(sizeof(*conn));
		child_process_init(conn);

		if (looks_like_command_line_option(path))
			die("strange pathname '%s' blocked", path);

		strbuf_addstr(&cmd, prog);
		strbuf_addch(&cmd, ' ');
		sq_quote_buf(&cmd, path);

		/* remove repo-local variables from the environment */
		conn->env = local_repo_env;
		conn->use_shell = 1;
		conn->in = conn->out = -1;
		if (protocol == PROTO_SSH) {
			const char *ssh;
			int putty = 0, tortoiseplink = 0;
			char *ssh_host = hostandport;
			const char *port = NULL;
			transport_check_allowed("ssh");
			get_host_and_port(&ssh_host, &port);

			if (!port)
