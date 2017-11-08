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