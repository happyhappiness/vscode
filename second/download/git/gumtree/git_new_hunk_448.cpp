		 * Separate original protocol components prog and path
		 * from extended host header with a NUL byte.
		 *
		 * Note: Do not add any other headers here!  Doing so
		 * will cause older git-daemon servers to crash.
		 */
		packet_write_fmt(fd[1],
			     "%s %s%chost=%s%c",
			     prog, path, 0,
			     target_host, 0);
		free(target_host);
	} else {
		conn = xmalloc(sizeof(*conn));
		child_process_init(conn);

		strbuf_addstr(&cmd, prog);
		strbuf_addch(&cmd, ' ');
		sq_quote_buf(&cmd, path);

		/* remove repo-local variables from the environment */
		conn->env = local_repo_env;
