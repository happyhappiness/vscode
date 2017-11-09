static int recurse_submodules_cb(const struct option *opt,
				 const char *arg, int unset)
{
	if (unset)
		string_list_clear((struct string_list *)opt->value, 0);
	else if (arg)
		string_list_append((struct string_list *)opt->value, arg);
	else
		string_list_append((struct string_list *)opt->value,
				   (const char *)opt->defval);

	return 0;
}