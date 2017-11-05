static int match_fragment(struct image *img,
			  struct image *preimage,
			  struct image *postimage,
			  unsigned long try,
			  int try_lno,
			  unsigned ws_rule,
			  int match_beginning, int match_end)
{
	int i;
	char *fixed_buf, *buf, *orig, *target;
	struct strbuf fixed;
	size_t fixed_len, postlen;
	int preimage_limit;

	if (preimage->nr + try_lno <= img->nr) {
		/*
		 * The hunk falls within the boundaries of img.
		 */
		preimage_limit = preimage->nr;
		if (match_end && (preimage->nr + try_lno != img->nr))
			return 0;
	} else if (ws_error_action == correct_ws_error &&
		   (ws_rule & WS_BLANK_AT_EOF)) {
		/*
		 * This hunk extends beyond the end of img, and we are
		 * removing blank lines at the end of the file.  This
		 * many lines from the beginning of the preimage must
		 * match with img, and the remainder of the preimage
		 * must be blank.
		 */
		preimage_limit = img->nr - try_lno;
	} else {
		/*
		 * The hunk extends beyond the end of the img and
		 * we are not removing blanks at the end, so we
		 * should reject the hunk at this position.
		 */
		return 0;
	}

	if (match_beginning && try_lno)
		return 0;

	/* Quick hash check */
	for (i = 0; i < preimage_limit; i++)
		if ((img->line[try_lno + i].flag & LINE_PATCHED) ||
		    (preimage->line[i].hash != img->line[try_lno + i].hash))
			return 0;

	if (preimage_limit == preimage->nr) {
		/*
		 * Do we have an exact match?  If we were told to match
		 * at the end, size must be exactly at try+fragsize,
		 * otherwise try+fragsize must be still within the preimage,
		 * and either case, the old piece should match the preimage
		 * exactly.
		 */
		if ((match_end
		     ? (try + preimage->len == img->len)
		     : (try + preimage->len <= img->len)) &&
		    !memcmp(img->buf + try, preimage->buf, preimage->len))
			return 1;
	} else {
		/*
		 * The preimage extends beyond the end of img, so
		 * there cannot be an exact match.
		 *
		 * There must be one non-blank context line that match
		 * a line before the end of img.
		 */
		char *buf_end;

		buf = preimage->buf;
		buf_end = buf;
		for (i = 0; i < preimage_limit; i++)
			buf_end += preimage->line[i].len;

		for ( ; buf < buf_end; buf++)
			if (!isspace(*buf))
				break;
		if (buf == buf_end)
			return 0;
	}

	/*
	 * No exact match. If we are ignoring whitespace, run a line-by-line
	 * fuzzy matching. We collect all the line length information because
	 * we need it to adjust whitespace if we match.
	 */
	if (ws_ignore_action == ignore_ws_change) {
		size_t imgoff = 0;
		size_t preoff = 0;
		size_t postlen = postimage->len;
		size_t extra_chars;
		char *preimage_eof;
		char *preimage_end;
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

	if (ws_error_action != correct_ws_error)
		return 0;

	/*
	 * The hunk does not apply byte-by-byte, but the hash says
	 * it might with whitespace fuzz. We weren't asked to
	 * ignore whitespace, we were asked to correct whitespace
	 * errors, so let's try matching after whitespace correction.
	 *
	 * While checking the preimage against the target, whitespace
	 * errors in both fixed, we count how large the corresponding
	 * postimage needs to be.  The postimage prepared by
	 * apply_one_fragment() has whitespace errors fixed on added
	 * lines already, but the common lines were propagated as-is,
	 * which may become longer when their whitespace errors are
	 * fixed.
	 */

	/* First count added lines in postimage */
	postlen = 0;
	for (i = 0; i < postimage->nr; i++) {
		if (!(postimage->line[i].flag & LINE_COMMON))
			postlen += postimage->line[i].len;
	}

	/*
	 * The preimage may extend beyond the end of the file,
	 * but in this loop we will only handle the part of the
	 * preimage that falls within the file.
	 */
	strbuf_init(&fixed, preimage->len + 1);
	orig = preimage->buf;
	target = img->buf + try;
	for (i = 0; i < preimage_limit; i++) {
		size_t oldlen = preimage->line[i].len;
		size_t tgtlen = img->line[try_lno + i].len;
		size_t fixstart = fixed.len;
		struct strbuf tgtfix;
		int match;

		/* Try fixing the line in the preimage */
		ws_fix_copy(&fixed, orig, oldlen, ws_rule, NULL);

		/* Try fixing the line in the target */
		strbuf_init(&tgtfix, tgtlen);
		ws_fix_copy(&tgtfix, target, tgtlen, ws_rule, NULL);

		/*
		 * If they match, either the preimage was based on
		 * a version before our tree fixed whitespace breakage,
		 * or we are lacking a whitespace-fix patch the tree
		 * the preimage was based on already had (i.e. target
		 * has whitespace breakage, the preimage doesn't).
		 * In either case, we are fixing the whitespace breakages
		 * so we might as well take the fix together with their
		 * real change.
		 */
		match = (tgtfix.len == fixed.len - fixstart &&
			 !memcmp(tgtfix.buf, fixed.buf + fixstart,
					     fixed.len - fixstart));

		/* Add the length if this is common with the postimage */
		if (preimage->line[i].flag & LINE_COMMON)
			postlen += tgtfix.len;

		strbuf_release(&tgtfix);
		if (!match)
			goto unmatch_exit;

		orig += oldlen;
		target += tgtlen;
	}


	/*
	 * Now handle the lines in the preimage that falls beyond the
	 * end of the file (if any). They will only match if they are
	 * empty or only contain whitespace (if WS_BLANK_AT_EOL is
	 * false).
	 */
	for ( ; i < preimage->nr; i++) {
		size_t fixstart = fixed.len; /* start of the fixed preimage */
		size_t oldlen = preimage->line[i].len;
		int j;

		/* Try fixing the line in the preimage */
		ws_fix_copy(&fixed, orig, oldlen, ws_rule, NULL);

		for (j = fixstart; j < fixed.len; j++)
			if (!isspace(fixed.buf[j]))
				goto unmatch_exit;

		orig += oldlen;
	}

	/*
	 * Yes, the preimage is based on an older version that still
	 * has whitespace breakages unfixed, and fixing them makes the
	 * hunk match.  Update the context lines in the postimage.
	 */
	fixed_buf = strbuf_detach(&fixed, &fixed_len);
	if (postlen < postimage->len)
		postlen = 0;
	update_pre_post_images(preimage, postimage,
			       fixed_buf, fixed_len, postlen);
	return 1;

 unmatch_exit:
	strbuf_release(&fixed);
	return 0;
}