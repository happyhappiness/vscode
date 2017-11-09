static void note_change_n(const char *p, struct branch *b, unsigned char *old_fanout)
{
	static struct strbuf uq = STRBUF_INIT;
	struct object_entry *oe;
	struct branch *s;
	struct object_id oid, commit_oid;
	char path[60];
	uint16_t inline_data = 0;
	unsigned char new_fanout;

	/*
	 * When loading a branch, we don't traverse its tree to count the real
	 * number of notes (too expensive to do this for all non-note refs).
	 * This means that recently loaded notes refs might incorrectly have
	 * b->num_notes == 0, and consequently, old_fanout might be wrong.
	 *
	 * Fix this by traversing the tree and counting the number of notes
	 * when b->num_notes == 0. If the notes tree is truly empty, the
	 * calculation should not take long.
	 */
	if (b->num_notes == 0 && *old_fanout == 0) {
		/* Invoke change_note_fanout() in "counting mode". */
		b->num_notes = change_note_fanout(&b->branch_tree, 0xff);
		*old_fanout = convert_num_notes_to_fanout(b->num_notes);
	}

	/* Now parse the notemodify command. */
	/* <dataref> or 'inline' */
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

	/* <commit-ish> */
	s = lookup_branch(p);
	if (s) {
		if (is_null_oid(&s->oid))
			die("Can't add a note on empty branch.");
		oidcpy(&commit_oid, &s->oid);
	} else if (*p == ':') {
		uintmax_t commit_mark = parse_mark_ref_eol(p);
		struct object_entry *commit_oe = find_mark(commit_mark);
		if (commit_oe->type != OBJ_COMMIT)
			die("Mark :%" PRIuMAX " not a commit", commit_mark);
		oidcpy(&commit_oid, &commit_oe->idx.oid);
	} else if (!get_oid(p, &commit_oid)) {
		unsigned long size;
		char *buf = read_object_with_reference(commit_oid.hash,
			commit_type, &size, commit_oid.hash);
		if (!buf || size < 46)
			die("Not a valid commit: %s", p);
		free(buf);
	} else
		die("Invalid ref name or SHA1 expression: %s", p);

	if (inline_data) {
		if (p != uq.buf) {
			strbuf_addstr(&uq, p);
			p = uq.buf;
		}
		read_next_command();
		parse_and_store_blob(&last_blob, &oid, 0);
	} else if (oe) {
		if (oe->type != OBJ_BLOB)
			die("Not a blob (actually a %s): %s",
				typename(oe->type), command_buf.buf);
	} else if (!is_null_oid(&oid)) {
		enum object_type type = sha1_object_info(oid.hash, NULL);
		if (type < 0)
			die("Blob not found: %s", command_buf.buf);
		if (type != OBJ_BLOB)
			die("Not a blob (actually a %s): %s",
			    typename(type), command_buf.buf);
	}

	construct_path_with_fanout(oid_to_hex(&commit_oid), *old_fanout, path);
	if (tree_content_remove(&b->branch_tree, path, NULL, 0))
		b->num_notes--;

	if (is_null_oid(&oid))
		return; /* nothing to insert */

	b->num_notes++;
	new_fanout = convert_num_notes_to_fanout(b->num_notes);
	construct_path_with_fanout(oid_to_hex(&commit_oid), new_fanout, path);
	tree_content_set(&b->branch_tree, path, &oid, S_IFREG | 0644, NULL);
}