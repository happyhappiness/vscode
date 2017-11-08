static int parse_bool(int *b, const char *k, const char *v)
{
	*b = git_config_bool(k, v);
	return 0;
}