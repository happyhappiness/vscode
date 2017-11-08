static unsigned long parse_oldstyle_date(const char *buf)
{
	char c, *p;
	char buffer[100];
	struct tm tm;
	const char *formats[] = {
		"%c",
		"%a %b %d %T",
		"%Z",
		"%Y",
		" %Y",
		NULL
	};
	/* We only ever did two timezones in the bad old format .. */
	const char *timezones[] = {
		"PDT", "PST", "CEST", NULL
	};
	const char **fmt = formats;

	p = buffer;
	while (isspace(c = *buf))
		buf++;
	while ((c = *buf++) != '\n')
		*p++ = c;
	*p++ = 0;
	buf = buffer;
	memset(&tm, 0, sizeof(tm));
	do {
		const char *next = strptime(buf, *fmt, &tm);
		if (next) {
			if (!*next)
				return mktime(&tm);
			buf = next;
		} else {
			const char **p = timezones;
			while (isspace(*buf))
				buf++;
			while (*p) {
				if (!memcmp(buf, *p, strlen(*p))) {
					buf += strlen(*p);
					break;
				}
				p++;
			}
		}
		fmt++;
	} while (*buf && *fmt);
	printf("left: %s\n", buf);
	return mktime(&tm);
}