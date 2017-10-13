static void process_tree(struct tree *tree,
			 struct object_array *p,
			 struct name_path *path,
			 const char *name,
			 struct connectivity_progress *cp)
{
	struct object *obj = &tree->object;
	struct tree_desc desc;
	struct name_entry entry;
	struct name_path me;

	if (!tree)
		die("bad tree object");
	if (obj->flags & SEEN)
		return;
	obj->flags |= SEEN;
	update_progress(cp);
	if (parse_tree(tree) < 0)
		die("bad tree object %s", sha1_to_hex(obj->sha1));
	add_object(obj, p, path, name);
	me.up = path;
	me.elem = name;
	me.elem_len = strlen(name);

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry)) {
		if (S_ISDIR(entry.mode))
			process_tree(lookup_tree(entry.sha1), p, &me, entry.path, cp);
		else if (S_ISGITLINK(entry.mode))
			process_gitlink(entry.sha1, p, &me, entry.path);
		else
			process_blob(lookup_blob(entry.sha1), p, &me, entry.path, cp);
	}
	free_tree_buffer(tree);
}