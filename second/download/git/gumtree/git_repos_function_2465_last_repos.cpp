static void *read_skip_worktree_file_from_index(const struct index_state *istate,
						const char *path, size_t *size,
						struct sha1_stat *sha1_stat)
{
	int pos, len;
	unsigned long sz;
	enum object_type type;
	void *data;

	len = strlen(path);
	pos = index_name_pos(istate, path, len);
	if (pos < 0)
		return NULL;
	if (!ce_skip_worktree(istate->cache[pos]))
		return NULL;
	data = read_sha1_file(istate->cache[pos]->oid.hash, &type, &sz);
	if (!data || type != OBJ_BLOB) {
		free(data);
		return NULL;
	}
	*size = xsize_t(sz);
	if (sha1_stat) {
		memset(&sha1_stat->stat, 0, sizeof(sha1_stat->stat));
		hashcpy(sha1_stat->sha1, istate->cache[pos]->oid.hash);
	}
	return data;
}