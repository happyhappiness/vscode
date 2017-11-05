int diff_root_tree_sha1(const unsigned char *new, const char *base, struct diff_options *opt)
{
	return diff_tree_sha1(NULL, new, base, opt);
}