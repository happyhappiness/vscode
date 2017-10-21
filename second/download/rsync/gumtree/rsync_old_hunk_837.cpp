				int j, len;
				close(fds[1]);
				set_blocking(fds[0]);
				len = read_arg_from_pipe(fds[0], buf, BIGPATHBUFLEN);
				if (len <= 0)
					_exit(1);
				if (asprintf(&p, "RSYNC_REQUEST=%s", buf) < 0)
					out_of_memory("rsync_module");
				putenv(p);
				for (j = 0; ; j++) {
					len = read_arg_from_pipe(fds[0], buf,
								 BIGPATHBUFLEN);
					if (len <= 0) {
						if (!len)
							break;
						_exit(1);
					}
					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) < 0)
						out_of_memory("rsync_module");
					putenv(p);
				}
				close(fds[0]);
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
				status = system(lp_prexfer_exec(i));
				if (!WIFEXITED(status))
