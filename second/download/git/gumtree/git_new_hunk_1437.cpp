	default:
		die("Corrupt mode: %s", command_buf.buf);
	}

	if (*p == ':') {
		oe = find_mark(parse_mark_ref_space(&p));
		oidcpy(&oid, &oe->idx.oid);
	} else if (skip_prefix(p, "inline ", &p)) {
		inline_data = 1;
		oe = NULL; /* not used with inline_data, but makes gcc happy */
	} else {
		if (parse_oid_hex(p, &oid, &p))
			die("Invalid dataref: %s", command_buf.buf);
		oe = find_object(&oid);
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
	if (S_ISDIR(mode) && is_empty_tree_oid(&oid) && *p) {
		tree_content_remove(&b->branch_tree, p, NULL, 0);
		return;
	}

	if (S_ISGITLINK(mode)) {
		if (inline_data)
