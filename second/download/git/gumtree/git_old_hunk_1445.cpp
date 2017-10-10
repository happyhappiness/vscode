	}

	if (oe->pack_id != MAX_PACK_ID) {	/* in a pack being written */
		buf = gfi_unpack_entry(oe, &size);
	} else {
		enum object_type unused;
		buf = read_sha1_file(sha1, &unused, &size);
	}
	if (!buf)
		die("Can't load object %s", sha1_to_hex(sha1));

	/* Peel one layer. */
	switch (oe->type) {
	case OBJ_TAG:
		if (size < 40 + strlen("object ") ||
		    get_sha1_hex(buf + strlen("object "), sha1))
			die("Invalid SHA1 in tag: %s", command_buf.buf);
		break;
	case OBJ_COMMIT:
		if (size < 40 + strlen("tree ") ||
		    get_sha1_hex(buf + strlen("tree "), sha1))
			die("Invalid SHA1 in commit: %s", command_buf.buf);
	}

	free(buf);
	return find_object(sha1);
}

static struct object_entry *parse_treeish_dataref(const char **p)
{
	unsigned char sha1[20];
	struct object_entry *e;

	if (**p == ':') {	/* <mark> */
		e = find_mark(parse_mark_ref_space(p));
		if (!e)
			die("Unknown mark: %s", command_buf.buf);
		hashcpy(sha1, e->idx.sha1);
	} else {	/* <sha1> */
		if (get_sha1_hex(*p, sha1))
			die("Invalid dataref: %s", command_buf.buf);
		e = find_object(sha1);
		*p += 40;
		if (*(*p)++ != ' ')
			die("Missing space after tree-ish: %s", command_buf.buf);
	}

	while (!e || e->type != OBJ_TREE)
		e = dereference(e, sha1);
	return e;
}

static void print_ls(int mode, const unsigned char *sha1, const char *path)
{
	static struct strbuf line = STRBUF_INIT;
