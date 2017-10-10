
	/* Now parse the notemodify command. */
	/* <dataref> or 'inline' */
	if (*p == ':') {
		oe = find_mark(parse_mark_ref_space(&p));
		hashcpy(sha1, oe->idx.sha1);
	} else if (skip_prefix(p, "inline ", &p)) {
		inline_data = 1;
		oe = NULL; /* not used with inline_data, but makes gcc happy */
	} else {
		if (get_sha1_hex(p, sha1))
			die("Invalid dataref: %s", command_buf.buf);
		oe = find_object(sha1);
		p += 40;
		if (*p++ != ' ')
			die("Missing space after SHA1: %s", command_buf.buf);
	}

	/* <commit-ish> */
	s = lookup_branch(p);
	if (s) {
		if (is_null_sha1(s->sha1))
			die("Can't add a note on empty branch.");
