static int is_empty_line(const char *line, int *len_p)
{
	int len = *len_p;
	while (len && isspace(line[len - 1]))
		len--;
	*len_p = len;
	return !len;
}