static void *read_skip_worktree_file_from_index(const char *path, size_t *size,
						struct sha1_stat *sha1_stat)
{
	int pos, len;
	unsigned long sz;
	enum object_type type;
	void *data;

	len = strlen(path);
	pos = cache_name_pos(path, len);
	if (pos < 0)
		return NULL;
	if (!ce_skip_worktree(active_cache[pos]))
		return NULL;
	data = read_sha1_file(active_cache[pos]->sha1, &type, &sz);
	if (!data || type != OBJ_BLOB) {
		free(data);
		return NULL;
	}
	*size = xsize_t(sz);
	if (sha1_stat) {
		memset(&sha1_stat->stat, 0, sizeof(sha1_stat->stat));
		hashcpy(sha1_stat->sha1, active_cache[pos]->sha1);
	}
	return data;
}