				sizeof(struct commit_graft *)
				* (commit_graft_nr - pos - 1));
	commit_graft_nr--;
	return 0;
}

int parse_commit_buffer(struct commit *item, const void *buffer, unsigned long size)
{
	const char *tail = buffer;
	const char *bufptr = buffer;
	unsigned char parent[20];
	struct commit_list **pptr;
