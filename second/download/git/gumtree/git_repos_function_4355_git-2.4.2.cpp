static char *find_name(const char *line, char *def, int p_value, int terminate)
{
	if (*line == '"') {
		char *name = find_name_gnu(line, def, p_value);
		if (name)
			return name;
	}

	return find_name_common(line, def, p_value, NULL, terminate);
}