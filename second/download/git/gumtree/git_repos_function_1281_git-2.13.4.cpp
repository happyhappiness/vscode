static void update_image(struct apply_state *state,
			 struct image *img,
			 int applied_pos,
			 struct image *preimage,
			 struct image *postimage)
{
	/*
	 * remove the copy of preimage at offset in img
	 * and replace it with postimage
	 */
	int i, nr;
	size_t remove_count, insert_count, applied_at = 0;
	char *result;
	int preimage_limit;

	/*
	 * If we are removing blank lines at the end of img,
	 * the preimage may extend beyond the end.
	 * If that is the case, we must be careful only to
	 * remove the part of the preimage that falls within
	 * the boundaries of img. Initialize preimage_limit
	 * to the number of lines in the preimage that falls
	 * within the boundaries.
	 */
	preimage_limit = preimage->nr;
	if (preimage_limit > img->nr - applied_pos)
		preimage_limit = img->nr - applied_pos;

	for (i = 0; i < applied_pos; i++)
		applied_at += img->line[i].len;

	remove_count = 0;
	for (i = 0; i < preimage_limit; i++)
		remove_count += img->line[applied_pos + i].len;
	insert_count = postimage->len;

	/* Adjust the contents */
	result = xmalloc(st_add3(st_sub(img->len, remove_count), insert_count, 1));
	memcpy(result, img->buf, applied_at);
	memcpy(result + applied_at, postimage->buf, postimage->len);
	memcpy(result + applied_at + postimage->len,
	       img->buf + (applied_at + remove_count),
	       img->len - (applied_at + remove_count));
	free(img->buf);
	img->buf = result;
	img->len += insert_count - remove_count;
	result[img->len] = '\0';

	/* Adjust the line table */
	nr = img->nr + postimage->nr - preimage_limit;
	if (preimage_limit < postimage->nr) {
		/*
		 * NOTE: this knows that we never call remove_first_line()
		 * on anything other than pre/post image.
		 */
		REALLOC_ARRAY(img->line, nr);
		img->line_allocated = img->line;
	}
	if (preimage_limit != postimage->nr)
		memmove(img->line + applied_pos + postimage->nr,
			img->line + applied_pos + preimage_limit,
			(img->nr - (applied_pos + preimage_limit)) *
			sizeof(*img->line));
	memcpy(img->line + applied_pos,
	       postimage->line,
	       postimage->nr * sizeof(*img->line));
	if (!state->allow_overlap)
		for (i = 0; i < postimage->nr; i++)
			img->line[applied_pos + i].flag |= LINE_PATCHED;
	img->nr = nr;
}