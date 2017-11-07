static void generate_id_list(void)
{
	unsigned char sha1[20], n[20];
	git_SHA_CTX ctx;
	int patchlen;
	struct strbuf line_buf = STRBUF_INIT;

	git_SHA1_Init(&ctx);
	hashclr(sha1);
	while (!feof(stdin)) {
		patchlen = get_one_patchid(n, &ctx, &line_buf);
		flush_current_id(patchlen, sha1, &ctx);
		hashcpy(sha1, n);
	}
	strbuf_release(&line_buf);
}