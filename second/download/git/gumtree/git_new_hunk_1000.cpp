				free(hostandport);
				free(path);
				free(conn);
				return NULL;
			}

			ssh = get_ssh_command();
			if (ssh)
				handle_ssh_variant(ssh, 1, &port_option,
						   &needs_batch);
			else {
				/*
				 * GIT_SSH is the no-shell version of
				 * GIT_SSH_COMMAND (and must remain so for
				 * historical compatibility).
				 */
				conn->use_shell = 0;

				ssh = getenv("GIT_SSH");
				if (!ssh)
					ssh = "ssh";
				else
					handle_ssh_variant(ssh, 0,
							   &port_option,
							   &needs_batch);
			}

			argv_array_push(&conn->args, ssh);
			if (flags & CONNECT_IPV4)
				argv_array_push(&conn->args, "-4");
			else if (flags & CONNECT_IPV6)
				argv_array_push(&conn->args, "-6");
			if (needs_batch)
				argv_array_push(&conn->args, "-batch");
			if (port) {
				argv_array_pushf(&conn->args,
						 "-%c", port_option);
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			transport_check_allowed("file");
		}
