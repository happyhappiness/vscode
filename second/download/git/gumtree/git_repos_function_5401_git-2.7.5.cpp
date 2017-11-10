static int stdin_diff_commit(struct commit *commit, char *line, int len)
{
	unsigned char sha1[20];
	if (isspace(line[40]) && !get_sha1_hex(line+41, sha1)) {
		/* Graft the fake parents locally to the commit */
		int pos = 41;
		struct commit_list **pptr;

		/* Free the real parent list */
		free_commit_list(commit->parents);
		commit->parents = NULL;
		pptr = &(commit->parents);
		while (line[pos] && !get_sha1_hex(line + pos, sha1)) {
			struct commit *parent = lookup_commit(sha1);
			if (parent) {
				pptr = &commit_list_insert(parent, pptr)->next;
			}
			pos += 41;
		}
	}
	return log_tree_commit(&log_tree_opt, commit);
}