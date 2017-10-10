				/* P is for PuTTY, p is for OpenSSH */
				argv_array_push(&conn->args, putty ? "-P" : "-p");
				argv_array_push(&conn->args, port);
			}
			argv_array_push(&conn->args, ssh_host);
		} else {
			transport_check_allowed("file");
		}
		argv_array_push(&conn->args, cmd.buf);

		if (start_command(conn))
			die("unable to fork");
