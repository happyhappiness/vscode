int utf8_strwidth(const char *string)
{
	return utf8_strnwidth(string, -1, 0);
}