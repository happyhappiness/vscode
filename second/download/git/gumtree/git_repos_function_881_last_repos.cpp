int unregister_shallow(const struct object_id *oid)
{
	int pos = commit_graft_pos(oid->hash);
	if (pos < 0)
		return -1;
	if (pos + 1 < commit_graft_nr)
		MOVE_ARRAY(commit_graft + pos, commit_graft + pos + 1,
			   commit_graft_nr - pos - 1);
	commit_graft_nr--;
	return 0;
}