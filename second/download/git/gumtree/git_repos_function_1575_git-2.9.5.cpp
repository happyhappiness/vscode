int color_parse(const char *value, char *dst)
{
	return color_parse_mem(value, strlen(value), dst);
}