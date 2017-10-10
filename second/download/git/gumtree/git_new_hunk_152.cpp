
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
