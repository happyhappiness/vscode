	unsigned char sha1[20], *pack_sig;
	off_t offset = 0, pack_sig_ofs = 0;
	uint32_t nr_objects, i;
	int err = 0;
	struct idx_entry *entries;

	if (!is_pack_valid(p))
		return error("packfile %s cannot be accessed", p->pack_name);

	git_SHA1_Init(&ctx);
	do {
		unsigned long remaining;
		unsigned char *in = use_pack(p, w_curs, offset, &remaining);
		offset += remaining;
