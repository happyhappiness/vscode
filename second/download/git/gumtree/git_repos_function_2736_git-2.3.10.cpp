static int handle_path(unsigned char *sha1, struct rerere_io *io, int marker_size)
{
	git_SHA_CTX ctx;
	int hunk_no = 0;
	enum {
		RR_CONTEXT = 0, RR_SIDE_1, RR_SIDE_2, RR_ORIGINAL
	} hunk = RR_CONTEXT;
	struct strbuf one = STRBUF_INIT, two = STRBUF_INIT;
	struct strbuf buf = STRBUF_INIT;

	if (sha1)
		git_SHA1_Init(&ctx);

	while (!io->getline(&buf, io)) {
		if (is_cmarker(buf.buf, '<', marker_size, 1)) {
			if (hunk != RR_CONTEXT)
				goto bad;
			hunk = RR_SIDE_1;
		} else if (is_cmarker(buf.buf, '|', marker_size, 0)) {
			if (hunk != RR_SIDE_1)
				goto bad;
			hunk = RR_ORIGINAL;
		} else if (is_cmarker(buf.buf, '=', marker_size, 0)) {
			if (hunk != RR_SIDE_1 && hunk != RR_ORIGINAL)
				goto bad;
			hunk = RR_SIDE_2;
		} else if (is_cmarker(buf.buf, '>', marker_size, 1)) {
			if (hunk != RR_SIDE_2)
				goto bad;
			if (strbuf_cmp(&one, &two) > 0)
				strbuf_swap(&one, &two);
			hunk_no++;
			hunk = RR_CONTEXT;
			rerere_io_putconflict('<', marker_size, io);
			rerere_io_putmem(one.buf, one.len, io);
			rerere_io_putconflict('=', marker_size, io);
			rerere_io_putmem(two.buf, two.len, io);
			rerere_io_putconflict('>', marker_size, io);
			if (sha1) {
				git_SHA1_Update(&ctx, one.buf ? one.buf : "",
					    one.len + 1);
				git_SHA1_Update(&ctx, two.buf ? two.buf : "",
					    two.len + 1);
			}
			strbuf_reset(&one);
			strbuf_reset(&two);
		} else if (hunk == RR_SIDE_1)
			strbuf_addbuf(&one, &buf);
		else if (hunk == RR_ORIGINAL)
			; /* discard */
		else if (hunk == RR_SIDE_2)
			strbuf_addbuf(&two, &buf);
		else
			rerere_io_putstr(buf.buf, io);
		continue;
	bad:
		hunk = 99; /* force error exit */
		break;
	}
	strbuf_release(&one);
	strbuf_release(&two);
	strbuf_release(&buf);

	if (sha1)
		git_SHA1_Final(sha1, &ctx);
	if (hunk != RR_CONTEXT)
		return -1;
	return hunk_no;
}