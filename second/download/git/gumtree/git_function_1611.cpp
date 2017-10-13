static char *resolve_symlink(char *p, size_t s)
{
	int depth = MAXDEPTH;

	while (depth--) {
		char link[PATH_MAX];
		int link_len = readlink(p, link, sizeof(link));
		if (link_len < 0) {
			/* not a symlink anymore */
			return p;
		}
		else if (link_len < sizeof(link))
			/* readlink() never null-terminates */
			link[link_len] = '\0';
		else {
			warning("%s: symlink too long", p);
			return p;
		}

		if (is_absolute_path(link)) {
			/* absolute path simply replaces p */
			if (link_len < s)
				strcpy(p, link);
			else {
				warning("%s: symlink too long", p);
				return p;
			}
		} else {
			/*
			 * link is a relative path, so I must replace the
			 * last element of p with it.
			 */
			char *r = (char *)last_path_elm(p);
			if (r - p + link_len < s)
				strcpy(r, link);
			else {
				warning("%s: symlink too long", p);
				return p;
			}
		}
	}
	return p;
}