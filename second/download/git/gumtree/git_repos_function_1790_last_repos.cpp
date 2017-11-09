static void load_tree(struct tree_entry *root)
{
	struct object_id *oid = &root->versions[1].oid;
	struct object_entry *myoe;
	struct tree_content *t;
	unsigned long size;
	char *buf;
	const char *c;

	root->tree = t = new_tree_content(8);
	if (is_null_oid(oid))
		return;

	myoe = find_object(oid);
	if (myoe && myoe->pack_id != MAX_PACK_ID) {
		if (myoe->type != OBJ_TREE)
			die("Not a tree: %s", oid_to_hex(oid));
		t->delta_depth = myoe->depth;
		buf = gfi_unpack_entry(myoe, &size);
		if (!buf)
			die("Can't load tree %s", oid_to_hex(oid));
	} else {
		enum object_type type;
		buf = read_sha1_file(oid->hash, &type, &size);
		if (!buf || type != OBJ_TREE)
			die("Can't load tree %s", oid_to_hex(oid));
	}

	c = buf;
	while (c != (buf + size)) {
		struct tree_entry *e = new_tree_entry();

		if (t->entry_count == t->entry_capacity)
			root->tree = t = grow_tree_content(t, t->entry_count);
		t->entries[t->entry_count++] = e;

		e->tree = NULL;
		c = get_mode(c, &e->versions[1].mode);
		if (!c)
			die("Corrupt mode in %s", oid_to_hex(oid));
		e->versions[0].mode = e->versions[1].mode;
		e->name = to_atom(c, strlen(c));
		c += e->name->str_len + 1;
		hashcpy(e->versions[0].oid.hash, (unsigned char *)c);
		hashcpy(e->versions[1].oid.hash, (unsigned char *)c);
		c += GIT_SHA1_RAWSZ;
	}
	free(buf);
}