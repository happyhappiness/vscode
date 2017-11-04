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