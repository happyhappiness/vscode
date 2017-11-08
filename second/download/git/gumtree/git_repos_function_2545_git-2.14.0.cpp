int diff_root_tree_oid(const struct object_id *new_oid, const char *base, struct diff_options *opt)
{
	return diff_tree_oid(NULL, new_oid, base, opt);
}