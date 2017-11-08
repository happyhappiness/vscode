int parse_opt_object_name(const struct option *opt, const char *arg, int unset)
{
	unsigned char sha1[20];

	if (unset) {
		sha1_array_clear(opt->value);
		return 0;
	}
	if (!arg)
		return -1;
	if (get_sha1(arg, sha1))
		return error(_("malformed object name '%s'"), arg);
	sha1_array_append(opt->value, sha1);
	return 0;
}