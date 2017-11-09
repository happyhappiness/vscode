static int read_tree_1(struct tree *tree, struct strbuf *base,
		       int stage, const struct pathspec *pathspec,
		       read_tree_fn_t fn, void *context)
{
	struct tree_desc desc;
	struct name_entry entry;
	struct object_id oid;
	int len, oldlen = base->len;
	enum interesting retval = entry_not_interesting;

	if (parse_tree(tree))
		return -1;

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry)) {
		if (retval != all_entries_interesting) {
			retval = tree_entry_interesting(&entry, base, 0, pathspec);
			if (retval == all_entries_not_interesting)
				break;
			if (retval == entry_not_interesting)
				continue;
		}

		switch (fn(entry.oid->hash, base,
			   entry.path, entry.mode, stage, context)) {
		case 0:
			continue;
		case READ_TREE_RECURSIVE:
			break;
		default:
			return -1;
		}

		if (S_ISDIR(entry.mode))
			oidcpy(&oid, entry.oid);
		else if (S_ISGITLINK(entry.mode)) {
			struct commit *commit;

			commit = lookup_commit(entry.oid);
			if (!commit)
				die("Commit %s in submodule path %s%s not found",
				    oid_to_hex(entry.oid),
				    base->buf, entry.path);

			if (parse_commit(commit))
				die("Invalid commit %s in submodule path %s%s",
				    oid_to_hex(entry.oid),
				    base->buf, entry.path);

			oidcpy(&oid, &commit->tree->object.oid);
		}
		else
			continue;

		len = tree_entry_len(&entry);
		strbuf_add(base, entry.path, len);
		strbuf_addch(base, '/');
		retval = read_tree_1(lookup_tree(&oid),
				     base, stage, pathspec,
				     fn, context);
		strbuf_setlen(base, oldlen);
		if (retval)
			return -1;
	}
	return 0;
}