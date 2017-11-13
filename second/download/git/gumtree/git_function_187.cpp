static void show_entry(struct diff_options *opt, const char *prefix,
		       struct tree_desc *desc, struct strbuf *base)
{
	unsigned mode;
	const char *path;
	const unsigned char *sha1 = tree_entry_extract(desc, &path, &mode);
	int pathlen = tree_entry_len(&desc->entry);
	int old_baselen = base->len;

	strbuf_add(base, path, pathlen);
	if (DIFF_OPT_TST(opt, RECURSIVE) && S_ISDIR(mode)) {
		enum object_type type;
		struct tree_desc inner;
		void *tree;
		unsigned long size;

		tree = read_sha1_file(sha1, &type, &size);
		if (!tree || type != OBJ_TREE)
			die("corrupt tree sha %s", sha1_to_hex(sha1));

		if (DIFF_OPT_TST(opt, TREE_IN_RECURSIVE))
			opt->add_remove(opt, *prefix, mode, sha1, 1, base->buf, 0);

		strbuf_addch(base, '/');

		init_tree_desc(&inner, tree, size);
		show_tree(opt, prefix, &inner, base);
		free(tree);
	} else
		opt->add_remove(opt, prefix[0], mode, sha1, 1, base->buf, 0);

	strbuf_setlen(base, old_baselen);
}