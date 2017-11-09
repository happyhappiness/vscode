static int rfc_callback(const struct option *opt, const char *arg, int unset)
{
	return subject_prefix_callback(opt, "RFC PATCH", unset);
}