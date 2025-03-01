static void process_tree(struct rev_info *revs,
			 struct tree *tree,
			 show_object_fn show,
			 struct name_path *path,
			 struct strbuf *base,
			 const char *name,
			 void *cb_data)
{
	struct object *obj = &tree->object;
	struct tree_desc desc;
	struct name_entry entry;
	struct name_path me;
	enum interesting match = revs->diffopt.pathspec.nr == 0 ?
		all_entries_interesting: entry_not_interesting;
	int baselen = base->len;

	if (!revs->tree_objects)
		return;
	if (!obj)
		die("bad tree object");
	if (obj->flags & (UNINTERESTING | SEEN))
		return;
	if (parse_tree(tree) < 0) {
		if (revs->ignore_missing_links)
			return;
		die("bad tree object %s", sha1_to_hex(obj->sha1));
	}
	obj->flags |= SEEN;
	show(obj, path, name, cb_data);
	me.up = path;
	me.elem = name;
	me.elem_len = strlen(name);

	if (!match) {
		strbuf_addstr(base, name);
		if (base->len)
			strbuf_addch(base, '/');
	}

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry)) {
		if (match != all_entries_interesting) {
			match = tree_entry_interesting(&entry, base, 0,
						       &revs->diffopt.pathspec);
			if (match == all_entries_not_interesting)
				break;
			if (match == entry_not_interesting)
				continue;
		}

		if (S_ISDIR(entry.mode))
			process_tree(revs,
				     lookup_tree(entry.sha1),
				     show, &me, base, entry.path,
				     cb_data);
		else if (S_ISGITLINK(entry.mode))
			process_gitlink(revs, entry.sha1,
					show, &me, entry.path,
					cb_data);
		else
			process_blob(revs,
				     lookup_blob(entry.sha1),
				     show, &me, entry.path,
				     cb_data);
	}
	strbuf_setlen(base, baselen);
	free_tree_buffer(tree);
}