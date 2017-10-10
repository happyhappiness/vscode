 */
int unpack_trees(unsigned len, struct tree_desc *t, struct unpack_trees_options *o)
{
	int i, ret;
	static struct cache_entry *dfc;
	struct exclude_list el;

	if (len > MAX_UNPACK_TREES)
		die("unpack_trees takes at most %d trees", MAX_UNPACK_TREES);
	memset(&state, 0, sizeof(state));
	state.base_dir = "";
	state.force = 1;
