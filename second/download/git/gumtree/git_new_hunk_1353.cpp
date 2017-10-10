
	/* prepare new parents */
	for (i = 0; i < argc; i++) {
		struct object_id oid;
		if (get_oid(argv[i], &oid) < 0)
			die(_("Not a valid object name: '%s'"), argv[i]);
		lookup_commit_or_die(&oid, argv[i]);
		strbuf_addf(&new_parents, "parent %s\n", oid_to_hex(&oid));
	}

	/* replace existing parents with new ones */
	strbuf_splice(buf, parent_start - buf->buf, parent_end - parent_start,
		      new_parents.buf, new_parents.len);
