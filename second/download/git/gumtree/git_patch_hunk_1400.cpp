 			     target_host, 0);
 		free(target_host);
 	} else {
 		conn = xmalloc(sizeof(*conn));
 		child_process_init(conn);
 
-		if (looks_like_command_line_option(path))
-			die("strange pathname '%s' blocked", path);
-
 		strbuf_addstr(&cmd, prog);
 		strbuf_addch(&cmd, ' ');
 		sq_quote_buf(&cmd, path);
 
 		/* remove repo-local variables from the environment */
 		conn->env = local_repo_env;
