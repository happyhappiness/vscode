int verify_pack_index(struct packed_git *p)
{
	off_t index_size;
	const unsigned char *index_base;
	git_SHA_CTX ctx;
	unsigned char sha1[20];
	int err = 0;

	if (open_pack_index(p))
		return error("packfile %s index not opened", p->pack_name);
	index_size = p->index_size;
	index_base = p->index_data;

	/* Verify SHA1 sum of the index file */
	git_SHA1_Init(&ctx);
	git_SHA1_Update(&ctx, index_base, (unsigned int)(index_size - 20));
	git_SHA1_Final(sha1, &ctx);
	if (hashcmp(sha1, index_base + index_size - 20))
		err = error("Packfile index for %s SHA1 mismatch",
			    p->pack_name);
	return err;
}