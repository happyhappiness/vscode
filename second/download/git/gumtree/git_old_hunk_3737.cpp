		msg_type = FSCK_WARN;

	append_msg_id(&sb, msg_id_info[id].id_string);

	va_start(ap, fmt);
	strbuf_vaddf(&sb, fmt, ap);
	result = options->error_func(object, msg_type, sb.buf);
	strbuf_release(&sb);
	va_end(ap);

	return result;
}

static int fsck_walk_tree(struct tree *tree, void *data, struct fsck_options *options)
{
	struct tree_desc desc;
	struct name_entry entry;
	int res = 0;

	if (parse_tree(tree))
		return -1;

	init_tree_desc(&desc, tree->buffer, tree->size);
	while (tree_entry(&desc, &entry)) {
		int result;

		if (S_ISGITLINK(entry.mode))
			continue;
		if (S_ISDIR(entry.mode))
			result = options->walk(&lookup_tree(entry.oid->hash)->object, OBJ_TREE, data, options);
		else if (S_ISREG(entry.mode) || S_ISLNK(entry.mode))
			result = options->walk(&lookup_blob(entry.oid->hash)->object, OBJ_BLOB, data, options);
		else {
			result = error("in tree %s: entry %s has bad mode %.6o",
					oid_to_hex(&tree->object.oid), entry.path, entry.mode);
		}
		if (result < 0)
			return result;
		if (!res)
			res = result;
	}
	return res;
}

static int fsck_walk_commit(struct commit *commit, void *data, struct fsck_options *options)
{
	struct commit_list *parents;
	int res;
	int result;

	if (parse_commit(commit))
		return -1;

	result = options->walk((struct object *)commit->tree, OBJ_TREE, data, options);
	if (result < 0)
		return result;
	res = result;

	parents = commit->parents;
	while (parents) {
		result = options->walk((struct object *)parents->item, OBJ_COMMIT, data, options);
		if (result < 0)
			return result;
		if (!res)
			res = result;
		parents = parents->next;
	}
	return res;
}

static int fsck_walk_tag(struct tag *tag, void *data, struct fsck_options *options)
{
	if (parse_tag(tag))
		return -1;
	return options->walk(tag->tagged, OBJ_ANY, data, options);
}

int fsck_walk(struct object *obj, void *data, struct fsck_options *options)
{
	if (!obj)
