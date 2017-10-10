			size = newsize;
		}

		fd = open_output_fd(path, ce, to_tempfile);
		if (fd < 0) {
			free(new);
			return error("unable to create file %s (%s)",
				path, strerror(errno));
		}

		wrote = write_in_full(fd, new, size);
		if (!to_tempfile)
			fstat_done = fstat_output(fd, state, &st);
		close(fd);
