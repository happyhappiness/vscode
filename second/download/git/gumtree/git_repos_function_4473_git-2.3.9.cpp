static void generate_id_list(int stable)
{
	unsigned char sha1[20], n[20], result[20];
	int patchlen;
	struct strbuf line_buf = STRBUF_INIT;

	hashclr(sha1);
	while (!feof(stdin)) {
		patchlen = get_one_patchid(n, result, &line_buf, stable);
		flush_current_id(patchlen, sha1, result);
		hashcpy(sha1, n);
	}
	strbuf_release(&line_buf);
}