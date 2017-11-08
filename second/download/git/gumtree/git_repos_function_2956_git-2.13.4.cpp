static const char *next_line(const char *str)
{
	const char *nl = strchrnul(str, '\n');
	return nl + !!*nl;
}