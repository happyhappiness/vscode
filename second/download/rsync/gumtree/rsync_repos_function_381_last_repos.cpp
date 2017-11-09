char *sanitize_path(char *dest, const char *p, const char *rootdir, int depth,
		    int flags)
{
	char *start, *sanp;
	int rlen = 0, drop_dot_dirs = !relative_paths || !(flags & SP_KEEP_DOT_DIRS);

	if (dest != p) {
		int plen = strlen(p);
		if (*p == '/') {
			if (!rootdir)
				rootdir = module_dir;
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

	if (drop_dot_dirs) {
		while (*p == '.' && p[1] == '/')
			p += 2;
	}

	start = sanp = dest + rlen;
	/* This loop iterates once per filename component in p, pointing at
	 * the start of the name (past any prior slash) for each iteration. */
	while (*p) {
		/* discard leading or extra slashes */
		if (*p == '/') {
			p++;
			continue;
		}
		if (drop_dot_dirs) {
			if (*p == '.' && (p[1] == '/' || p[1] == '\0')) {
				/* skip "." component */
				p++;
				continue;
			}
		}
		if (*p == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0')) {
			/* ".." component followed by slash or end */
			if (depth <= 0 || sanp != start) {
				p += 2;
				if (sanp != start) {
					/* back up sanp one level */
					--sanp; /* now pointing at slash */
					while (sanp > start && sanp[-1] != '/')
						sanp--;
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