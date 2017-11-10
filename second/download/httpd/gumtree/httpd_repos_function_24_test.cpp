int find_commit_subject(const char *commit_buffer, const char **subject)
{
	const char *eol;
	const char *p = commit_buffer;

	while (*p && (*p != '\n' || p[1] != '\n'))
		p++;
	if (*p) {
		p += 2;
		for (eol = p; *eol && *eol != '\n'; eol++)
			; /* do nothing */
	} else
		eol = p;

	*subject = p;

	return eol - p;
}