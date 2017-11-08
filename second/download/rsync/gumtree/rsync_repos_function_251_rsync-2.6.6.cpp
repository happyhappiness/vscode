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