static void update_pre_post_images(struct image *preimage,
				   struct image *postimage,
				   char *buf,
				   size_t len, size_t postlen)
{
	int i, ctx, reduced;
	char *new, *old, *fixed;
	struct image fixed_preimage;

	/*
	 * Update the preimage with whitespace fixes.  Note that we
	 * are not losing preimage->buf -- apply_one_fragment() will
	 * free "oldlines".
	 */
	prepare_image(&fixed_preimage, buf, len, 1);
	assert(postlen
	       ? fixed_preimage.nr == preimage->nr
	       : fixed_preimage.nr <= preimage->nr);
	for (i = 0; i < fixed_preimage.nr; i++)
		fixed_preimage.line[i].flag = preimage->line[i].flag;
	free(preimage->line_allocated);
	*preimage = fixed_preimage;

	/*
	 * Adjust the common context lines in postimage. This can be
	 * done in-place when we are shrinking it with whitespace
	 * fixing, but needs a new buffer when ignoring whitespace or
	 * expanding leading tabs to spaces.
	 *
	 * We trust the caller to tell us if the update can be done
	 * in place (postlen==0) or not.
	 */
	old = postimage->buf;
	if (postlen)
		new = postimage->buf = xmalloc(postlen);
	else
		new = old;
	fixed = preimage->buf;

	for (i = reduced = ctx = 0; i < postimage->nr; i++) {
		size_t l_len = postimage->line[i].len;
		if (!(postimage->line[i].flag & LINE_COMMON)) {
			/* an added line -- no counterparts in preimage */
			memmove(new, old, l_len);
			old += l_len;
			new += l_len;
			continue;
		}

		/* a common context -- skip it in the original postimage */
		old += l_len;

		/* and find the corresponding one in the fixed preimage */
		while (ctx < preimage->nr &&
		       !(preimage->line[ctx].flag & LINE_COMMON)) {
			fixed += preimage->line[ctx].len;
			ctx++;
		}

		/*
		 * preimage is expected to run out, if the caller
		 * fixed addition of trailing blank lines.
		 */
		if (preimage->nr <= ctx) {
			reduced++;
			continue;
		}

		/* and copy it in, while fixing the line length */
		l_len = preimage->line[ctx].len;
		memcpy(new, fixed, l_len);
		new += l_len;
		fixed += l_len;
		postimage->line[i].len = l_len;
		ctx++;
	}

	if (postlen
	    ? postlen < new - postimage->buf
	    : postimage->len < new - postimage->buf)
		die("BUG: caller miscounted postlen: asked %d, orig = %d, used = %d",
		    (int)postlen, (int) postimage->len, (int)(new - postimage->buf));

	/* Fix the length of the whole thing */
	postimage->len = new - postimage->buf;
	postimage->nr -= reduced;
}