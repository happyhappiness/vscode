	}

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
		hashcpy(commit_sha1, s->sha1);
	} else if (*p == ':') {
		uintmax_t commit_mark = parse_mark_ref_eol(p);
		struct object_entry *commit_oe = find_mark(commit_mark);
		if (commit_oe->type != OBJ_COMMIT)
			die("Mark :%" PRIuMAX " not a commit", commit_mark);
		hashcpy(commit_sha1, commit_oe->idx.sha1);
	} else if (!get_sha1(p, commit_sha1)) {
		unsigned long size;
		char *buf = read_object_with_reference(commit_sha1,
			commit_type, &size, commit_sha1);
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
		parse_and_store_blob(&last_blob, sha1, 0);
	} else if (oe) {
		if (oe->type != OBJ_BLOB)
			die("Not a blob (actually a %s): %s",
				typename(oe->type), command_buf.buf);
	} else if (!is_null_sha1(sha1)) {
		enum object_type type = sha1_object_info(sha1, NULL);
		if (type < 0)
			die("Blob not found: %s", command_buf.buf);
		if (type != OBJ_BLOB)
			die("Not a blob (actually a %s): %s",
			    typename(type), command_buf.buf);
	}

	construct_path_with_fanout(sha1_to_hex(commit_sha1), *old_fanout, path);
	if (tree_content_remove(&b->branch_tree, path, NULL, 0))
		b->num_notes--;

	if (is_null_sha1(sha1))
		return; /* nothing to insert */

	b->num_notes++;
	new_fanout = convert_num_notes_to_fanout(b->num_notes);
	construct_path_with_fanout(sha1_to_hex(commit_sha1), new_fanout, path);
	tree_content_set(&b->branch_tree, path, sha1, S_IFREG | 0644, NULL);
}

static void file_change_deleteall(struct branch *b)
{
	release_tree_content_recursive(b->branch_tree.tree);
	hashclr(b->branch_tree.versions[0].sha1);
	hashclr(b->branch_tree.versions[1].sha1);
	load_tree(&b->branch_tree);
	b->num_notes = 0;
}

static void parse_from_commit(struct branch *b, char *buf, unsigned long size)
{
	if (!buf || size < 46)
		die("Not a valid commit: %s", sha1_to_hex(b->sha1));
	if (memcmp("tree ", buf, 5)
		|| get_sha1_hex(buf + 5, b->branch_tree.versions[1].sha1))
		die("The commit %s is corrupt", sha1_to_hex(b->sha1));
	hashcpy(b->branch_tree.versions[0].sha1,
		b->branch_tree.versions[1].sha1);
}

static void parse_from_existing(struct branch *b)
{
	if (is_null_sha1(b->sha1)) {
		hashclr(b->branch_tree.versions[0].sha1);
		hashclr(b->branch_tree.versions[1].sha1);
	} else {
		unsigned long size;
		char *buf;

		buf = read_object_with_reference(b->sha1,
			commit_type, &size, b->sha1);
		parse_from_commit(b, buf, size);
		free(buf);
	}
}

static int parse_from(struct branch *b)
{
	const char *from;
	struct branch *s;
	unsigned char sha1[20];

	if (!skip_prefix(command_buf.buf, "from ", &from))
		return 0;

	hashcpy(sha1, b->branch_tree.versions[1].sha1);

	s = lookup_branch(from);
	if (b == s)
		die("Can't create a branch from itself: %s", b->name);
	else if (s) {
		unsigned char *t = s->branch_tree.versions[1].sha1;
		hashcpy(b->sha1, s->sha1);
		hashcpy(b->branch_tree.versions[0].sha1, t);
		hashcpy(b->branch_tree.versions[1].sha1, t);
	} else if (*from == ':') {
		uintmax_t idnum = parse_mark_ref_eol(from);
		struct object_entry *oe = find_mark(idnum);
		if (oe->type != OBJ_COMMIT)
			die("Mark :%" PRIuMAX " not a commit", idnum);
		if (hashcmp(b->sha1, oe->idx.sha1)) {
			hashcpy(b->sha1, oe->idx.sha1);
			if (oe->pack_id != MAX_PACK_ID) {
				unsigned long size;
				char *buf = gfi_unpack_entry(oe, &size);
				parse_from_commit(b, buf, size);
				free(buf);
			} else
				parse_from_existing(b);
		}
	} else if (!get_sha1(from, b->sha1)) {
		parse_from_existing(b);
		if (is_null_sha1(b->sha1))
			b->delete = 1;
	}
	else
		die("Invalid ref name or SHA1 expression: %s", from);

	if (b->branch_tree.tree && hashcmp(sha1, b->branch_tree.versions[1].sha1)) {
		release_tree_content_recursive(b->branch_tree.tree);
		b->branch_tree.tree = NULL;
	}

	read_next_command();
	return 1;
