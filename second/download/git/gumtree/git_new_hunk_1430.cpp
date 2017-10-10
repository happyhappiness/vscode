		struct tree_entry *e = t->entries[i];
		if (!e->versions[v].mode)
			continue;
		strbuf_addf(b, "%o %s%c",
			(unsigned int)(e->versions[v].mode & ~NO_DELTA),
			e->name->str_dat, '\0');
		strbuf_add(b, e->versions[v].oid.hash, GIT_SHA1_RAWSZ);
	}
}

static void store_tree(struct tree_entry *root)
{
	struct tree_content *t;
	unsigned int i, j, del;
	struct last_object lo = { STRBUF_INIT, 0, 0, /* no_swap */ 1 };
	struct object_entry *le = NULL;

	if (!is_null_oid(&root->versions[1].oid))
		return;

	if (!root->tree)
		load_tree(root);
	t = root->tree;

	for (i = 0; i < t->entry_count; i++) {
		if (t->entries[i]->tree)
			store_tree(t->entries[i]);
	}

	if (!(root->versions[0].mode & NO_DELTA))
		le = find_object(&root->versions[0].oid);
	if (S_ISDIR(root->versions[0].mode) && le && le->pack_id == pack_id) {
		mktree(t, 0, &old_tree);
		lo.data = old_tree;
		lo.offset = le->idx.offset;
		lo.depth = t->delta_depth;
	}

	mktree(t, 1, &new_tree);
	store_object(OBJ_TREE, &new_tree, &lo, &root->versions[1].oid, 0);

	t->delta_depth = lo.depth;
	for (i = 0, j = 0, del = 0; i < t->entry_count; i++) {
		struct tree_entry *e = t->entries[i];
		if (e->versions[1].mode) {
			e->versions[0].mode = e->versions[1].mode;
			oidcpy(&e->versions[0].oid, &e->versions[1].oid);
			t->entries[j++] = e;
		} else {
			release_tree_entry(e);
			del++;
		}
	}
	t->entry_count -= del;
}

static void tree_content_replace(
	struct tree_entry *root,
	const struct object_id *oid,
	const uint16_t mode,
	struct tree_content *newtree)
{
	if (!S_ISDIR(mode))
		die("Root cannot be a non-directory");
	oidclr(&root->versions[0].oid);
	oidcpy(&root->versions[1].oid, oid);
	if (root->tree)
		release_tree_content_recursive(root->tree);
	root->tree = newtree;
}

static int tree_content_set(
	struct tree_entry *root,
	const char *p,
	const struct object_id *oid,
	const uint16_t mode,
	struct tree_content *subtree)
{
	struct tree_content *t;
	const char *slash1;
	unsigned int i, n;
