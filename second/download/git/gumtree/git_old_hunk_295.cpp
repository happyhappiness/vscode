	unsigned char sha1[20], *pack_sig;
	off_t offset = 0, pack_sig_ofs = 0;
	uint32_t nr_objects, i;
	int err = 0;
	struct idx_entry *entries;

	/* Note that the pack header checks are actually performed by
	 * use_pack when it first opens the pack file.  If anything
	 * goes wrong during those checks then the call will die out
	 * immediately.
	 */

	git_SHA1_Init(&ctx);
	do {
		unsigned long remaining;
		unsigned char *in = use_pack(p, w_curs, offset, &remaining);
		offset += remaining;
