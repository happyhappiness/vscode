static char *find_name_traditional(const char *line, char *def, int p_value)
{
	size_t len;
	size_t date_len;

	if (*line == '"') {
		char *name = find_name_gnu(line, def, p_value);
		if (name)
			return name;
	}

	len = strchrnul(line, '\n') - line;
	date_len = diff_timestamp_len(line, len);
	if (!date_len)
		return find_name_common(line, def, p_value, NULL, TERM_TAB);
	len -= date_len;

	return find_name_common(line, def, p_value, line + len, 0);
}