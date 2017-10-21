	*dest = '\0';
	va_end(ap);

	return ret;
}

int count_dir_elements(const char *p)
{
	int cnt = 0, new_component = 1;
	while (*p) {
		if (*p++ == '/')
			new_component = 1;
		else if (new_component) {
			new_component = 0;
			cnt++;
		}
	}
	return cnt;
}

/* Turns multiple adjacent slashes into a single slash, gets rid of "./"
 * elements (but not a trailing dot dir), removes a trailing slash, and
 * optionally collapses ".." elements (except for those at the start of the
 * string).  If the resulting name would be empty, change it into a ".". */
unsigned int clean_fname(char *name, BOOL collapse_dot_dot)
{
	char *limit = name - 1, *t = name, *f = name;
	int anchored;

	if (!name)
		return 0;

	if ((anchored = *f == '/') != 0)
		*t++ = *f++;
	while (*f) {
		/* discard extra slashes */
		if (*f == '/') {
			f++;
			continue;
		}
		if (*f == '.') {
			/* discard "." dirs (but NOT a trailing '.'!) */
			if (f[1] == '/') {
				f += 2;
				continue;
			}
			/* collapse ".." dirs */
			if (collapse_dot_dot
			    && f[1] == '.' && (f[2] == '/' || !f[2])) {
				char *s = t - 1;
				if (s == name && anchored) {
					f += 2;
					continue;
				}
				while (s > limit && *--s != '/') {}
				if (s != t - 1 && (s < name || *s == '/')) {
					t = s + 1;
					f += 2;
					continue;
				}
				limit = t + 2;
			}
		}
		while (*f && (*t++ = *f++) != '/') {}
	}

	if (t > name+anchored && t[-1] == '/')
		t--;
	if (t == name)
		*t++ = '.';
	*t = '\0';

	return t - name;
}

/* Make path appear as if a chroot had occurred.  This handles a leading
 * "/" (either removing it or expanding it) and any leading or embedded
 * ".." components that attempt to escape past the module's top dir.
 *
 * If dest is NULL, a buffer is allocated to hold the result.  It is legal
 * to call with the dest and the path (p) pointing to the same buffer, but
 * rootdir will be ignored to avoid expansion of the string.
 *
 * The rootdir string contains a value to use in place of a leading slash.
 * Specify NULL to get the default of lp_path(module_id).
 *
 * If depth is >= 0, it is a count of how many '..'s to allow at the start
 * of the path.  Use -1 to allow unlimited depth.
 *
 * We also clean the path in a manner similar to clean_fname() but with a
 * few differences: 
 *
 * Turns multiple adjacent slashes into a single slash, gets rid of "." dir
 * elements (INCLUDING a trailing dot dir), PRESERVES a trailing slash, and
 * ALWAYS collapses ".." elements (except for those at the start of the
 * string up to "depth" deep).  If the resulting name would be empty,
 * change it into a ".". */
char *sanitize_path(char *dest, const char *p, const char *rootdir, int depth)
{
	char *start, *sanp;
	int rlen = 0;

	if (dest != p) {
		int plen = strlen(p);
		if (*p == '/') {
			if (!rootdir)
				rootdir = lp_path(module_id);
			rlen = strlen(rootdir);
			depth = 0;
			p++;
		}
		if (dest) {
			if (rlen + plen + 1 >= MAXPATHLEN)
				return NULL;
		} else if (!(dest = new_array(char, rlen + plen + 1)))
			out_of_memory("sanitize_path");
		if (rlen) {
			memcpy(dest, rootdir, rlen);
			if (rlen > 1)
				dest[rlen++] = '/';
		}
	}

	start = sanp = dest + rlen;
	while (*p != '\0') {
		/* discard leading or extra slashes */
		if (*p == '/') {
			p++;
			continue;
		}
		/* this loop iterates once per filename component in p.
		 * both p (and sanp if the original had a slash) should
		 * always be left pointing after a slash
		 */
		if (*p == '.' && (p[1] == '/' || p[1] == '\0')) {
			/* skip "." component */
			p++;
			continue;
		}
		if (*p == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0')) {
			/* ".." component followed by slash or end */
			if (depth <= 0 || sanp != start) {
				p += 2;
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
			/* allow depth levels of .. at the beginning */
			depth--;
			/* move the virtual beginning to leave the .. alone */
			start = sanp + 3;
		}
		/* copy one component through next slash */
		while (*p && (*sanp++ = *p++) != '/') {}
	}
	if (sanp == dest) {
		/* ended up with nothing, so put in "." component */
		*sanp++ = '.';
	}
	*sanp = '\0';

	return dest;
}

char curr_dir[MAXPATHLEN];
unsigned int curr_dir_len;

/**
