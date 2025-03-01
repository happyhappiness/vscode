static int line_by_line_fuzzy_match(struct image *img,
				    struct image *preimage,
				    struct image *postimage,
				    unsigned long try,
				    int try_lno,
				    int preimage_limit)
{
	int i;
	size_t imgoff = 0;
	size_t preoff = 0;
	size_t postlen = postimage->len;
	size_t extra_chars;
	char *buf;
	char *preimage_eof;
	char *preimage_end;
	struct strbuf fixed;
	char *fixed_buf;
	size_t fixed_len;

	for (i = 0; i < preimage_limit; i++) {
		size_t prelen = preimage->line[i].len;
		size_t imglen = img->line[try_lno+i].len;

		if (!fuzzy_matchlines(img->buf + try + imgoff, imglen,
				      preimage->buf + preoff, prelen))
			return 0;
		if (preimage->line[i].flag & LINE_COMMON)
			postlen += imglen - prelen;
		imgoff += imglen;
		preoff += prelen;
	}

	/*
	 * Ok, the preimage matches with whitespace fuzz.
	 *
	 * imgoff now holds the true length of the target that
	 * matches the preimage before the end of the file.
	 *
	 * Count the number of characters in the preimage that fall
	 * beyond the end of the file and make sure that all of them
	 * are whitespace characters. (This can only happen if
	 * we are removing blank lines at the end of the file.)
	 */
	buf = preimage_eof = preimage->buf + preoff;
	for ( ; i < preimage->nr; i++)
		preoff += preimage->line[i].len;
	preimage_end = preimage->buf + preoff;
	for ( ; buf < preimage_end; buf++)
		if (!isspace(*buf))
			return 0;

	/*
	 * Update the preimage and the common postimage context
	 * lines to use the same whitespace as the target.
	 * If whitespace is missing in the target (i.e.
	 * if the preimage extends beyond the end of the file),
	 * use the whitespace from the preimage.
	 */
	extra_chars = preimage_end - preimage_eof;
	strbuf_init(&fixed, imgoff + extra_chars);
	strbuf_add(&fixed, img->buf + try, imgoff);
	strbuf_add(&fixed, preimage_eof, extra_chars);
	fixed_buf = strbuf_detach(&fixed, &fixed_len);
	update_pre_post_images(preimage, postimage,
			       fixed_buf, fixed_len, postlen);
	return 1;
}