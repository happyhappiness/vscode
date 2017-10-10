 */
int unpack_trees(unsigned len, struct tree_desc *t, struct unpack_trees_options *o)
{
	int i, ret;
	static struct cache_entry *dfc;
	struct exclude_list el;

	if (len > MAX_UNPACK_TREES)
		die("unpack_trees takes at most %d trees", MAX_UNPACK_TREES);

	memset(&el, 0, sizeof(el));
	if (!core_apply_sparse_checkout || !o->update)
		o->skip_sparse_checkout = 1;
	if (!o->skip_sparse_checkout) {
		char *sparse = git_pathdup("info/sparse-checkout");
