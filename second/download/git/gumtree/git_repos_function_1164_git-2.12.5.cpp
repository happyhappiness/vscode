static size_t tz_with_colon_len(const char *line, size_t len)
{
	const char *tz, *p;

	if (len < strlen(" +08:00") || line[len - strlen(":00")] != ':')
		return 0;
	tz = line + len - strlen(" +08:00");

	if (tz[0] != ' ' || (tz[1] != '+' && tz[1] != '-'))
		return 0;
	p = tz + 2;
	if (!isdigit(*p++) || !isdigit(*p++) || *p++ != ':' ||
	    !isdigit(*p++) || !isdigit(*p++))
		return 0;

	return line + len - tz;
}