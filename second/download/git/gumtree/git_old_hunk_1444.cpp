		free(buf);
}

static void parse_get_mark(const char *p)
{
	struct object_entry *oe = oe;
	char output[42];

	/* get-mark SP <object> LF */
	if (*p != ':')
		die("Not a mark: %s", p);

	oe = find_mark(parse_mark_ref_eol(p));
	if (!oe)
		die("Unknown mark: %s", command_buf.buf);

	xsnprintf(output, sizeof(output), "%s\n", sha1_to_hex(oe->idx.sha1));
	cat_blob_write(output, 41);
}

static void parse_cat_blob(const char *p)
{
	struct object_entry *oe = oe;
	unsigned char sha1[20];

	/* cat-blob SP <object> LF */
	if (*p == ':') {
		oe = find_mark(parse_mark_ref_eol(p));
		if (!oe)
			die("Unknown mark: %s", command_buf.buf);
		hashcpy(sha1, oe->idx.sha1);
	} else {
		if (get_sha1_hex(p, sha1))
			die("Invalid dataref: %s", command_buf.buf);
		if (p[40])
			die("Garbage after SHA1: %s", command_buf.buf);
		oe = find_object(sha1);
	}

	cat_blob(oe, sha1);
}

static struct object_entry *dereference(struct object_entry *oe,
					unsigned char sha1[20])
{
	unsigned long size;
	char *buf = NULL;
	if (!oe) {
		enum object_type type = sha1_object_info(sha1, NULL);
		if (type < 0)
			die("object not found: %s", sha1_to_hex(sha1));
		/* cache it! */
		oe = insert_object(sha1);
		oe->type = type;
		oe->pack_id = MAX_PACK_ID;
		oe->idx.offset = 1;
	}
	switch (oe->type) {
	case OBJ_TREE:	/* easy case. */
