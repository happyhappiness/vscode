		free(buf);
}

static void parse_get_mark(const char *p)
{
	struct object_entry *oe = oe;
	char output[GIT_MAX_HEXSZ + 2];

	/* get-mark SP <object> LF */
	if (*p != ':')
		die("Not a mark: %s", p);

	oe = find_mark(parse_mark_ref_eol(p));
	if (!oe)
		die("Unknown mark: %s", command_buf.buf);

	xsnprintf(output, sizeof(output), "%s\n", oid_to_hex(&oe->idx.oid));
	cat_blob_write(output, GIT_SHA1_HEXSZ + 1);
}

static void parse_cat_blob(const char *p)
{
	struct object_entry *oe = oe;
	struct object_id oid;

	/* cat-blob SP <object> LF */
	if (*p == ':') {
		oe = find_mark(parse_mark_ref_eol(p));
		if (!oe)
			die("Unknown mark: %s", command_buf.buf);
		oidcpy(&oid, &oe->idx.oid);
	} else {
		if (parse_oid_hex(p, &oid, &p))
			die("Invalid dataref: %s", command_buf.buf);
		if (*p)
			die("Garbage after SHA1: %s", command_buf.buf);
		oe = find_object(&oid);
	}

	cat_blob(oe, &oid);
}

static struct object_entry *dereference(struct object_entry *oe,
					struct object_id *oid)
{
	unsigned long size;
	char *buf = NULL;
	if (!oe) {
		enum object_type type = sha1_object_info(oid->hash, NULL);
		if (type < 0)
			die("object not found: %s", oid_to_hex(oid));
		/* cache it! */
		oe = insert_object(oid);
		oe->type = type;
		oe->pack_id = MAX_PACK_ID;
		oe->idx.offset = 1;
	}
	switch (oe->type) {
	case OBJ_TREE:	/* easy case. */
