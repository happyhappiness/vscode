static int pickaxe_match(struct diff_filepair *p, struct diff_options *o,
			 regex_t *regexp, kwset_t kws, pickaxe_fn fn)
{
	struct userdiff_driver *textconv_one = NULL;
	struct userdiff_driver *textconv_two = NULL;
	mmfile_t mf1, mf2;
	int ret;

	if (!o->pickaxe[0])
		return 0;

	/* ignore unmerged */
	if (!DIFF_FILE_VALID(p->one) && !DIFF_FILE_VALID(p->two))
		return 0;

	if (DIFF_OPT_TST(o, ALLOW_TEXTCONV)) {
		textconv_one = get_textconv(p->one);
		textconv_two = get_textconv(p->two);
	}

	/*
	 * If we have an unmodified pair, we know that the count will be the
	 * same and don't even have to load the blobs. Unless textconv is in
	 * play, _and_ we are using two different textconv filters (e.g.,
	 * because a pair is an exact rename with different textconv attributes
	 * for each side, which might generate different content).
	 */
	if (textconv_one == textconv_two && diff_unmodified_pair(p))
		return 0;

	mf1.size = fill_textconv(textconv_one, p->one, &mf1.ptr);
	mf2.size = fill_textconv(textconv_two, p->two, &mf2.ptr);

	ret = fn(DIFF_FILE_VALID(p->one) ? &mf1 : NULL,
		 DIFF_FILE_VALID(p->two) ? &mf2 : NULL,
		 o, regexp, kws);

	if (textconv_one)
		free(mf1.ptr);
	if (textconv_two)
		free(mf2.ptr);
	diff_free_filespec_data(p->one);
	diff_free_filespec_data(p->two);

	return ret;
}