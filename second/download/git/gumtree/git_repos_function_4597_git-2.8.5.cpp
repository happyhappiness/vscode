static size_t short_time_len(const char *line, size_t len)
{
	const char *time, *p;

	if (len < strlen(" 07:01:32") || line[len-strlen(":32")] != ':')
		return 0;
	p = time = line + len - strlen(" 07:01:32");

	/* Permit 1-digit hours? */
	if (*p++ != ' ' ||
	    !isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++))	/* Not a time. */
		return 0;

	return line + len - time;
}