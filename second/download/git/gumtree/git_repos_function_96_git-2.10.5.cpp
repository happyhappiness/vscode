static int is_blank_line(const char *line, int *len_p)
{
	int len = *len_p;
	while (len && isspace(line[len - 1]))
		len--;
	*len_p = len;
	return !len;
}