static void read_stat(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	if (rd->data + sizeof(struct stat_data) > rd->end) {
		rd->data = rd->end + 1;
		return;
	}
	stat_data_from_disk(&ud->stat_data, rd->data);
	rd->data += sizeof(struct stat_data);
	ud->valid = 1;
}