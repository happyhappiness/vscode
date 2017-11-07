void color_parse(const char *value, const char *var, char *dst)
{
	color_parse_mem(value, strlen(value), var, dst);
}