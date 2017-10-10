		die("Corrupt mode: %s", command_buf.buf);
	}

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

	strbuf_reset(&uq);
	if (!unquote_c_style(&uq, p, &endp)) {
		if (*endp)
			die("Garbage after path in: %s", command_buf.buf);
		p = uq.buf;
	}

	/* Git does not track empty, non-toplevel directories. */
	if (S_ISDIR(mode) && !hashcmp(sha1, EMPTY_TREE_SHA1_BIN) && *p) {
		tree_content_remove(&b->branch_tree, p, NULL, 0);
		return;
	}

	if (S_ISGITLINK(mode)) {
		if (inline_data)
