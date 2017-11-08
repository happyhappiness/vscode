static long apply_delta(off_t len, struct line_buffer *input,
			const char *old_data, uint32_t old_mode)
{
	long ret;
	struct sliding_view preimage = SLIDING_VIEW_INIT(&report_buffer, 0);
	FILE *out;

	if (init_postimage() || !(out = buffer_tmpfile_rewind(&postimage)))
		die("cannot open temporary file for blob retrieval");
	if (old_data) {
		const char *response;
		printf("cat-blob %s\n", old_data);
		fflush(stdout);
		response = get_response_line();
		if (parse_cat_response_line(response, &preimage.max_off))
			die("invalid cat-blob response: %s", response);
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (old_mode == REPO_MODE_LNK) {
		strbuf_addstr(&preimage.buf, "link ");
		check_preimage_overflow(preimage.max_off, strlen("link "));
		preimage.max_off += strlen("link ");
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (svndiff0_apply(input, len, &preimage, out))
		die("cannot apply delta");
	if (old_data) {
		/* Read the remainder of preimage and trailing newline. */
		assert(!signed_add_overflows(preimage.max_off, 1));
		preimage.max_off++;	/* room for newline */
		if (move_window(&preimage, preimage.max_off - 1, 1))
			die("cannot seek to end of input");
		if (preimage.buf.buf[0] != '\n')
			die("missing newline after cat-blob response");
	}
	ret = buffer_tmpfile_prepare_to_read(&postimage);
	if (ret < 0)
		die("cannot read temporary file for blob retrieval");
	strbuf_release(&preimage.buf);
	return ret;
}