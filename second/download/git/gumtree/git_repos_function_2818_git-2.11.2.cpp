static int find_separator(const char *line, const char *separators)
{
	int loc = strcspn(line, separators);
	if (!line[loc])
		return -1;
	return loc;
}