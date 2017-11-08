static void add_nocompress_suffixes(const char *str)
{
	char *buf, *t;
	const char *f = str;

	if (!(buf = new_array(char, strlen(f) + 1)))
		out_of_memory("add_nocompress_suffixes");

	while (*f) {
		if (*f == '/') {
			f++;
			continue;
		}

		t = buf;
		do {
			if (isUpper(f))
				*t++ = toLower(f);
			else
				*t++ = *f;
		} while (*++f != '/' && *f);
		*t++ = '\0';

		add_suffix(&suftree, *buf, buf+1);
	}

	free(buf);
}