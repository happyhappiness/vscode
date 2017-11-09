static int commit_graft_pos(const unsigned char *sha1)
{
	return sha1_pos(sha1, commit_graft, commit_graft_nr,
			commit_graft_sha1_access);
}