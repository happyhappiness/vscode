int register_commit_graft(struct commit_graft *graft, int ignore_dups)
{
	int pos = commit_graft_pos(graft->oid.hash);

	if (0 <= pos) {
		if (ignore_dups)
			free(graft);
		else {
			free(commit_graft[pos]);
			commit_graft[pos] = graft;
		}
		return 1;
	}
	pos = -pos - 1;
	ALLOC_GROW(commit_graft, commit_graft_nr + 1, commit_graft_alloc);
	commit_graft_nr++;
	if (pos < commit_graft_nr)
		memmove(commit_graft + pos + 1,
			commit_graft + pos,
			(commit_graft_nr - pos - 1) *
			sizeof(*commit_graft));
	commit_graft[pos] = graft;
	return 0;
}