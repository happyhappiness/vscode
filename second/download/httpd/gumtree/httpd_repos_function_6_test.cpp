static const unsigned char *commit_graft_sha1_access(size_t index, void *table)
{
	struct commit_graft **commit_graft_table = table;
	return commit_graft_table[index]->oid.hash;
}