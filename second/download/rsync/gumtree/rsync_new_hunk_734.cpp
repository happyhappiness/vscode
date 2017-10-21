	}
	while (*p != '\0') {
		/* this loop iterates once per filename component in p.
		 * both p (and sanp if the original had a slash) should
		 * always be left pointing after a slash
		 */
		if (*p == '.' && (p[1] == '/' || p[1] == '\0')) {
			/* skip "." component */
			while (*++p == '/') {
				/* skip following slashes */
				;
			}
			continue;
		}
		allowdotdot = 0;
		if (*p == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0')) {
			/* ".." component followed by slash or end */
			if (depth > 0 && sanp == start) {
				/* allow depth levels of .. at the beginning */
				--depth;
				allowdotdot = 1;
			} else {
				p += 2;
				if (*p == '/')
					p++;
				if (sanp != start) {
					/* back up sanp one level */
					--sanp; /* now pointing at slash */
					while (sanp > start && sanp[-1] != '/') {
						/* skip back up to slash */
						sanp--;
					}
				}
				continue;
			}
		}
		while (1) {
			/* copy one component through next slash */
			*sanp++ = *p++;
			if (*p == '\0' || p[-1] == '/') {
				while (*p == '/') {
					/* skip multiple slashes */
					p++;
				}
				break;
			}
		}
		if (allowdotdot) {
			/* move the virtual beginning to leave the .. alone */
			start = sanp;
		}
	}
	if (sanp == start && !allowdotdot) {
		/* ended up with nothing, so put in "." component */
		/*
		 * note that the !allowdotdot doesn't prevent this from
		 *  happening in all allowed ".." situations, but I didn't
		 *  think it was worth putting in an extra variable to ensure
		 *  it since an extra "." won't hurt in those situations.
		 */
		*sanp++ = '.';
	}
	*sanp = '\0';
}

/* Works much like sanitize_path(), with these differences:  (1) a new buffer
 * is allocated for the sanitized path rather than modifying it in-place; (2)
 * a leading slash gets transformed into the rootdir value (which can be empty
 * or NULL if you just want the slash to get dropped); (3) no "reldir" can be
 * specified. */
char *alloc_sanitize_path(const char *path, const char *rootdir)
{
	char *buf;
	int rlen, plen = strlen(path);

	if (*path == '/' && rootdir) {
		rlen = strlen(rootdir);
		if (rlen == 1)
			path++;
	} else
		rlen = 0;
	if (!(buf = new_array(char, rlen + plen + 1)))
		out_of_memory("alloc_sanitize_path");
	if (rlen)
		memcpy(buf, rootdir, rlen);
	memcpy(buf + rlen, path, plen + 1);

	if (rlen > 1)
		rlen++;
	sanitize_path(buf + rlen, NULL);
	if (rlen && buf[rlen] == '.' && buf[rlen+1] == '\0') {
		if (rlen > 1)
			rlen--;
		buf[rlen] = '\0';
	}

	return buf;
}

char curr_dir[MAXPATHLEN];
unsigned int curr_dir_len;

/**
 * Like chdir(), but it keeps track of the current directory (in the
 * global "curr_dir"), and ensures that the path size doesn't overflow.
 * Also cleans the path using the clean_fname() function.
 **/
int push_dir(char *dir)
{
	static int initialised;
	unsigned int len;

	if (!initialised) {
		initialised = 1;
		getcwd(curr_dir, sizeof curr_dir - 1);
		curr_dir_len = strlen(curr_dir);
	}

	if (!dir)	/* this call was probably just to initialize */
		return 0;

	len = strlen(dir);
	if (len == 1 && *dir == '.')
		return 1;

	if ((*dir == '/' ? len : curr_dir_len + 1 + len) >= sizeof curr_dir)
		return 0;

	if (chdir(dir))
		return 0;

	if (*dir == '/') {
		memcpy(curr_dir, dir, len + 1);
		curr_dir_len = len;
	} else {
		curr_dir[curr_dir_len++] = '/';
		memcpy(curr_dir + curr_dir_len, dir, len + 1);
		curr_dir_len += len;
	}

	clean_fname(curr_dir);

	return 1;
}

/**
 * Reverse a push_dir() call.  You must pass in an absolute path
 * that was copied from a prior value of "curr_dir".
 **/
int pop_dir(char *dir)
{
	if (chdir(dir))
		return 0;

	curr_dir_len = strlcpy(curr_dir, dir, sizeof curr_dir);
	if (curr_dir_len >= sizeof curr_dir)
		curr_dir_len = sizeof curr_dir - 1;

	return 1;
}

/**
 * Return a quoted string with the full pathname of the indicated filename.
 * The string " (in MODNAME)" may also be appended.  The returned pointer
 * remains valid until the next time full_fname() is called.
