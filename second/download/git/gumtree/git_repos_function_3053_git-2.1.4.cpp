int verify_pack(struct packed_git *p, verify_fn fn,
		struct progress *progress, uint32_t base_count)
{
	int err = 0;
	struct pack_window *w_curs = NULL;

	err |= verify_pack_index(p);
	if (!p->index_data)
		return -1;

	err |= verify_packfile(p, &w_curs, fn, progress, base_count);
	unuse_pack(&w_curs);

	return err;
}