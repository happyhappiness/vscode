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