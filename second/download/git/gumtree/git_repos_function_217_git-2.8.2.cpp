void diff_tree_combined_merge(const struct commit *commit, int dense,
			      struct rev_info *rev)
{
	struct commit_list *parent = get_saved_parents(rev, commit);
	struct sha1_array parents = SHA1_ARRAY_INIT;

	while (parent) {
		sha1_array_append(&parents, parent->item->object.oid.hash);
		parent = parent->next;
	}
	diff_tree_combined(commit->object.oid.hash, &parents, dense, rev);
	sha1_array_clear(&parents);
}