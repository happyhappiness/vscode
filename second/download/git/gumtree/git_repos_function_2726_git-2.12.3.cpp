char *strbuf_realpath(struct strbuf *resolved, const char *path,
		      int die_on_error)
{
	struct strbuf remaining = STRBUF_INIT;
	struct strbuf next = STRBUF_INIT;
	struct strbuf symlink = STRBUF_INIT;
	char *retval = NULL;
	int num_symlinks = 0;
	struct stat st;

	if (!*path) {
		if (die_on_error)
			die("The empty string is not a valid path");
		else
			goto error_out;
	}

	strbuf_addstr(&remaining, path);
	get_root_part(resolved, &remaining);

	if (!resolved->len) {
		/* relative path; can use CWD as the initial resolved path */
		if (strbuf_getcwd(resolved)) {
			if (die_on_error)
				die_errno("unable to get current working directory");
			else
				goto error_out;
		}
	}

	/* Iterate over the remaining path components */
	while (remaining.len > 0) {
		get_next_component(&next, &remaining);

		if (next.len == 0) {
			continue; /* empty component */
		} else if (next.len == 1 && !strcmp(next.buf, ".")) {
			continue; /* '.' component */
		} else if (next.len == 2 && !strcmp(next.buf, "..")) {
			/* '..' component; strip the last path component */
			strip_last_component(resolved);
			continue;
		}

		/* append the next component and resolve resultant path */
		if (!is_dir_sep(resolved->buf[resolved->len - 1]))
			strbuf_addch(resolved, '/');
		strbuf_addbuf(resolved, &next);

		if (lstat(resolved->buf, &st)) {
			/* error out unless this was the last component */
			if (errno != ENOENT || remaining.len) {
				if (die_on_error)
					die_errno("Invalid path '%s'",
						  resolved->buf);
				else
					goto error_out;
			}
		} else if (S_ISLNK(st.st_mode)) {
			ssize_t len;
			strbuf_reset(&symlink);

			if (num_symlinks++ > MAXSYMLINKS) {
				errno = ELOOP;

				if (die_on_error)
					die("More than %d nested symlinks "
					    "on path '%s'", MAXSYMLINKS, path);
				else
					goto error_out;
			}

			len = strbuf_readlink(&symlink, resolved->buf,
					      st.st_size);
			if (len < 0) {
				if (die_on_error)
					die_errno("Invalid symlink '%s'",
						  resolved->buf);
				else
					goto error_out;
			}

			if (is_absolute_path(symlink.buf)) {
				/* absolute symlink; set resolved to root */
				get_root_part(resolved, &symlink);
			} else {
				/*
				 * relative symlink
				 * strip off the last component since it will
				 * be replaced with the contents of the symlink
				 */
				strip_last_component(resolved);
			}

			/*
			 * if there are still remaining components to resolve
			 * then append them to symlink
			 */
			if (remaining.len) {
				strbuf_addch(&symlink, '/');
				strbuf_addbuf(&symlink, &remaining);
			}

			/*
			 * use the symlink as the remaining components that
			 * need to be resloved
			 */
			strbuf_swap(&symlink, &remaining);
		}
	}

	retval = resolved->buf;

error_out:
	strbuf_release(&remaining);
	strbuf_release(&next);
	strbuf_release(&symlink);

	if (!retval)
		strbuf_reset(resolved);

	return retval;
}