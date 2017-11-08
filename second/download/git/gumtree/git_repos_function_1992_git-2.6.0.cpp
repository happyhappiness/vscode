static void set_check_only(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	ud->check_only = 1;
}