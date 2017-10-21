	*dest = '\0';
	va_end(ap);

	return ret;
}

void clean_fname(char *name)
{
	char *p;
	int l;
	int modified = 1;

	if (!name) return;

	while (modified) {
		modified = 0;

		if ((p = strstr(name,"/./")) != NULL) {
			modified = 1;
			while (*p) {
				p[0] = p[2];
				p++;
			}
		}

		if ((p = strstr(name,"//")) != NULL) {
			modified = 1;
			while (*p) {
				p[0] = p[1];
				p++;
			}
		}

		if (strncmp(p = name, "./", 2) == 0) {
			modified = 1;
			do {
				p[0] = p[2];
			} while (*p++);
		}

		l = strlen(p = name);
		if (l > 1 && p[l-1] == '/') {
			modified = 1;
			p[l-1] = 0;
		}
	}
}

/**
 * Make path appear as if a chroot had occurred:
 *
 * @li 1. remove leading "/" (or replace with "." if at end)
 *
 * @li 2. remove leading ".." components (except those allowed by @p reldir)
 *
 * @li 3. delete any other "<dir>/.." (recursively)
 *
 * Can only shrink paths, so sanitizes in place.
 *
 * While we're at it, remove double slashes and "." components like
 *   clean_fname() does, but DON'T remove a trailing slash because that
 *   is sometimes significant on command line arguments.
 *
 * If @p reldir is non-null, it is a sanitized directory that the path will be
 *    relative to, so allow as many ".." at the beginning of the path as
 *    there are components in reldir.  This is used for symbolic link targets.
 *    If reldir is non-null and the path began with "/", to be completely like
 *    a chroot we should add in depth levels of ".." at the beginning of the
 *    path, but that would blow the assumption that the path doesn't grow and
 *    it is not likely to end up being a valid symlink anyway, so just do
 *    the normal removal of the leading "/" instead.
 *
 * Contributed by Dave Dykstra <dwd@bell-labs.com>
 */
void sanitize_path(char *p, char *reldir)
{
	char *start, *sanp;
	int depth = 0;
	int allowdotdot = 0;

	if (reldir) {
		depth++;
		while (*reldir) {
			if (*reldir++ == '/') {
				depth++;
			}
		}
	}
	start = p;
	sanp = p;
	while (*p == '/') {
		/* remove leading slashes */
		p++;
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
