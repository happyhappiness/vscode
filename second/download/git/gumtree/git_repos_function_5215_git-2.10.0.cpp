static int to_callback(const struct option *opt, const char *arg, int unset)
{
	if (unset)
		string_list_clear(&extra_to, 0);
	else
		string_list_append(&extra_to, arg);
	return 0;
}