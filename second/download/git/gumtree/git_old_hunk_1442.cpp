
	/* from ... */
	if (!skip_prefix(command_buf.buf, "from ", &from))
		die("Expected from command, got %s", command_buf.buf);
	s = lookup_branch(from);
	if (s) {
		if (is_null_sha1(s->sha1))
			die("Can't tag an empty branch.");
		hashcpy(sha1, s->sha1);
		type = OBJ_COMMIT;
	} else if (*from == ':') {
		struct object_entry *oe;
		from_mark = parse_mark_ref_eol(from);
		oe = find_mark(from_mark);
		type = oe->type;
		hashcpy(sha1, oe->idx.sha1);
	} else if (!get_sha1(from, sha1)) {
		struct object_entry *oe = find_object(sha1);
		if (!oe) {
			type = sha1_object_info(sha1, NULL);
			if (type < 0)
				die("Not a valid object: %s", from);
		} else
			type = oe->type;
	} else
		die("Invalid ref name or SHA1 expression: %s", from);
