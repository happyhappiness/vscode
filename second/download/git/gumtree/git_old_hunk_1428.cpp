	*modep = mode;
	return str;
}

static void load_tree(struct tree_entry *root)
{
	unsigned char *sha1 = root->versions[1].sha1;
	struct object_entry *myoe;
	struct tree_content *t;
	unsigned long size;
	char *buf;
	const char *c;

	root->tree = t = new_tree_content(8);
	if (is_null_sha1(sha1))
		return;

	myoe = find_object(sha1);
	if (myoe && myoe->pack_id != MAX_PACK_ID) {
		if (myoe->type != OBJ_TREE)
			die("Not a tree: %s", sha1_to_hex(sha1));
		t->delta_depth = myoe->depth;
		buf = gfi_unpack_entry(myoe, &size);
		if (!buf)
			die("Can't load tree %s", sha1_to_hex(sha1));
	} else {
		enum object_type type;
		buf = read_sha1_file(sha1, &type, &size);
		if (!buf || type != OBJ_TREE)
			die("Can't load tree %s", sha1_to_hex(sha1));
	}

	c = buf;
	while (c != (buf + size)) {
		struct tree_entry *e = new_tree_entry();

