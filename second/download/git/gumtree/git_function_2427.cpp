tatic int parse_opt_points_at(const struct option *opt __attribute__((unused)),
			const char *arg, int unset)
{
	unsigned char sha1[20];

	if (unset) {
		sha1_array_clear(&points_at);
		return 0;
	}
	if (!arg)
		return error(_("switch 'points-at' requires an object"));
	if (get_sha1(arg, sha1))
		return error(_("malformed object name '%s'"), arg);
	sha1_array_append(&points_at, sha1);
	return 0;
}