void diff_tree_combined_merge(const struct commit *commit, int dense,
			      struct rev_info *rev)
{
	struct commit_list *parent = get_saved_parents(rev, commit);
	struct oid_array parents = OID_ARRAY_INIT;

	while (parent) {
		oid_array_append(&parents, &parent->item->object.oid);
		parent = parent->next;
	}
	diff_tree_combined(&commit->object.oid, &parents, dense, rev);
	oid_array_clear(&parents);
}