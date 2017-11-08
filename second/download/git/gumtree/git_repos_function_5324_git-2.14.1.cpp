static int shared_callback(const struct option *opt, const char *arg, int unset)
{
	*((int *) opt->value) = (arg) ? git_config_perm("arg", arg) : PERM_GROUP;
	return 0;
}