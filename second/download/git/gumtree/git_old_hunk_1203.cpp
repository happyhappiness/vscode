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
