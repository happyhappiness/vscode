static void read_sha1(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	if (rd->data + 20 > rd->end) {
		rd->data = rd->end + 1;
		return;
	}
	hashcpy(ud->exclude_sha1, rd->data);
	rd->data += 20;
}