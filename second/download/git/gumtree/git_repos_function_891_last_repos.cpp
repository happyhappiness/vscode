int find_commit_subject(const char *commit_buffer, const char **subject)
{
	const char *eol;
	const char *p = commit_buffer;

	while (*p && (*p != '\n' || p[1] != '\n'))
		p++;
	if (*p) {
		p = skip_blank_lines(p + 2);
		eol = strchrnul(p, '\n');
	} else
		eol = p;

	*subject = p;

	return eol - p;
}