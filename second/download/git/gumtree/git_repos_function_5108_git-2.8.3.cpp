static int cc_callback(const struct option *opt, const char *arg, int unset)
{
	if (unset)
		string_list_clear(&extra_cc, 0);
	else
		string_list_append(&extra_cc, arg);
	return 0;
}