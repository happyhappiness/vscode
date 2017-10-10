 *
 * If path is our buffer, then return path, as it's already what the
 * user wants.
 */
static const char *real_path_internal(const char *path, int die_on_error)
{
	static char bufs[2][PATH_MAX + 1], *buf = bufs[0], *next_buf = bufs[1];
	char *retval = NULL;

	/*
	 * If we have to temporarily chdir(), store the original CWD
	 * here so that we can chdir() back to it at the end of the
	 * function:
	 */
	char cwd[1024] = "";

	int buf_index = 1;

	int depth = MAXDEPTH;
	char *last_elem = NULL;
	struct stat st;

	/* We've already done it */
	if (path == buf || path == next_buf)
		return path;

	if (!*path) {
		if (die_on_error)
			die("The empty string is not a valid path");
		else
			goto error_out;
	}

	if (strlcpy(buf, path, PATH_MAX) >= PATH_MAX) {
		if (die_on_error)
			die("Too long path: %.*s", 60, path);
		else
			goto error_out;
	}

	while (depth--) {
		if (!is_directory(buf)) {
			char *last_slash = find_last_dir_sep(buf);
			if (last_slash) {
				last_elem = xstrdup(last_slash + 1);
				last_slash[1] = '\0';
			} else {
				last_elem = xstrdup(buf);
				*buf = '\0';
			}
		}

		if (*buf) {
			if (!*cwd && !getcwd(cwd, sizeof(cwd))) {
				if (die_on_error)
					die_errno("Could not get current working directory");
				else
					goto error_out;
			}

			if (chdir(buf)) {
				if (die_on_error)
					die_errno("Could not switch to '%s'", buf);
				else
					goto error_out;
			}
		}
		if (!getcwd(buf, PATH_MAX)) {
			if (die_on_error)
				die_errno("Could not get current working directory");
			else
				goto error_out;
		}

		if (last_elem) {
			size_t len = strlen(buf);
			if (len + strlen(last_elem) + 2 > PATH_MAX) {
				if (die_on_error)
					die("Too long path name: '%s/%s'",
					    buf, last_elem);
				else
					goto error_out;
			}
			if (len && !is_dir_sep(buf[len - 1]))
				buf[len++] = '/';
			strcpy(buf + len, last_elem);
			free(last_elem);
			last_elem = NULL;
		}

		if (!lstat(buf, &st) && S_ISLNK(st.st_mode)) {
			ssize_t len = readlink(buf, next_buf, PATH_MAX);
			if (len < 0) {
				if (die_on_error)
					die_errno("Invalid symlink '%s'", buf);
				else
					goto error_out;
			}
			if (PATH_MAX <= len) {
				if (die_on_error)
					die("symbolic link too long: %s", buf);
				else
					goto error_out;
			}
			next_buf[len] = '\0';
			buf = next_buf;
			buf_index = 1 - buf_index;
			next_buf = bufs[buf_index];
		} else
			break;
	}

	retval = buf;
error_out:
	free(last_elem);
	if (*cwd && chdir(cwd))
		die_errno("Could not change back to '%s'", cwd);

	return retval;
}

const char *real_path(const char *path)
{
