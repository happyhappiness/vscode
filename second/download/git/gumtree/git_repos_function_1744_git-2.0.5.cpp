static int compare_tree_entry(struct tree_desc *t1, struct tree_desc *t2,
			      struct strbuf *base, struct diff_options *opt)
{
	unsigned mode1, mode2;
	const char *path1, *path2;
	const unsigned char *sha1, *sha2;
	int cmp, pathlen1, pathlen2;
	int old_baselen = base->len;

	sha1 = tree_entry_extract(t1, &path1, &mode1);
	sha2 = tree_entry_extract(t2, &path2, &mode2);

	pathlen1 = tree_entry_len(&t1->entry);
	pathlen2 = tree_entry_len(&t2->entry);
	cmp = base_name_compare(path1, pathlen1, mode1, path2, pathlen2, mode2);
	if (cmp < 0) {
		show_entry(opt, "-", t1, base);
		return -1;
	}
	if (cmp > 0) {
		show_entry(opt, "+", t2, base);
		return 1;
	}
	if (!DIFF_OPT_TST(opt, FIND_COPIES_HARDER) && !hashcmp(sha1, sha2) && mode1 == mode2)
		return 0;

	/*
	 * If the filemode has changed to/from a directory from/to a regular
	 * file, we need to consider it a remove and an add.
	 */
	if (S_ISDIR(mode1) != S_ISDIR(mode2)) {
		show_entry(opt, "-", t1, base);
		show_entry(opt, "+", t2, base);
		return 0;
	}

	strbuf_add(base, path1, pathlen1);
	if (DIFF_OPT_TST(opt, RECURSIVE) && S_ISDIR(mode1)) {
		if (DIFF_OPT_TST(opt, TREE_IN_RECURSIVE)) {
			opt->change(opt, mode1, mode2,
				    sha1, sha2, 1, 1, base->buf, 0, 0);
		}
		strbuf_addch(base, '/');
		diff_tree_sha1(sha1, sha2, base->buf, opt);
	} else {
		opt->change(opt, mode1, mode2, sha1, sha2, 1, 1, base->buf, 0, 0);
	}
	strbuf_setlen(base, old_baselen);
	return 0;
}