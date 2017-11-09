int unregister_shallow(const unsigned char *sha1)
{
	int pos = commit_graft_pos(sha1);
	if (pos < 0)
		return -1;
	if (pos + 1 < commit_graft_nr)
		memmove(commit_graft + pos, commit_graft + pos + 1,
				sizeof(struct commit_graft *)
				* (commit_graft_nr - pos - 1));
	commit_graft_nr--;
	return 0;
}