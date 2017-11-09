static int stdin_diff_commit(struct commit *commit, const char *p)
{
	struct object_id oid;
	struct commit_list **pptr = NULL;

	/* Graft the fake parents locally to the commit */
	while (isspace(*p++) && !parse_oid_hex(p, &oid, &p)) {
		struct commit *parent = lookup_commit(&oid);
		if (!pptr) {
			/* Free the real parent list */
			free_commit_list(commit->parents);
			commit->parents = NULL;
			pptr = &(commit->parents);
		}
		if (parent) {
			pptr = &commit_list_insert(parent, pptr)->next;
		}
	}
	return log_tree_commit(&log_tree_opt, commit);
}