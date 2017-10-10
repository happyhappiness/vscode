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
