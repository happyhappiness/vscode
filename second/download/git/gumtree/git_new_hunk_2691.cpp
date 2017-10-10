			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			/* remove repo-local variables from the environment */
			conn->env = local_repo_env;
			conn->use_shell = 1;
			transport_check_allowed("file");
		}
		argv_array_push(&conn->args, cmd.buf);

		if (start_command(conn))
			die("unable to fork");

