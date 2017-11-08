static char *get_nth_line(long line, unsigned long *ends, void *data)
{
	if (line == 0)
		return (char *)data;
	else
		return (char *)data + ends[line] + 1;
}