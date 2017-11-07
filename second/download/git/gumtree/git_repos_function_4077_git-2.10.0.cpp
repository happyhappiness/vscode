static void load_subtree(struct notes_tree *t, struct leaf_node *subtree,
		struct int_node *node, unsigned int n)
{
	unsigned char object_sha1[20];
	unsigned int prefix_len;
	void *buf;
	struct tree_desc desc;
	struct name_entry entry;
	int len, path_len;
	unsigned char type;
	struct leaf_node *l;

	buf = fill_tree_descriptor(&desc, subtree->val_sha1);
	if (!buf)
		die("Could not read %s for notes-index",
		     sha1_to_hex(subtree->val_sha1));

	prefix_len = subtree->key_sha1[19];
	assert(prefix_len * 2 >= n);
	memcpy(object_sha1, subtree->key_sha1, prefix_len);
	while (tree_entry(&desc, &entry)) {
		path_len = strlen(entry.path);
		len = get_sha1_hex_segment(entry.path, path_len,
				object_sha1 + prefix_len, 20 - prefix_len);
		if (len < 0)
			goto handle_non_note; /* entry.path is not a SHA1 */
		len += prefix_len;

		/*
		 * If object SHA1 is complete (len == 20), assume note object
		 * If object SHA1 is incomplete (len < 20), and current
		 * component consists of 2 hex chars, assume note subtree
		 */
		if (len <= 20) {
			type = PTR_TYPE_NOTE;
			l = (struct leaf_node *)
				xcalloc(1, sizeof(struct leaf_node));
			hashcpy(l->key_sha1, object_sha1);
			hashcpy(l->val_sha1, entry.oid->hash);
			if (len < 20) {
				if (!S_ISDIR(entry.mode) || path_len != 2)
					goto handle_non_note; /* not subtree */
				l->key_sha1[19] = (unsigned char) len;
				type = PTR_TYPE_SUBTREE;
			}
			if (note_tree_insert(t, node, n, l, type,
					     combine_notes_concatenate))
				die("Failed to load %s %s into notes tree "
				    "from %s",
				    type == PTR_TYPE_NOTE ? "note" : "subtree",
				    sha1_to_hex(l->key_sha1), t->ref);
		}
		continue;

handle_non_note:
		/*
		 * Determine full path for this non-note entry:
		 * The filename is already found in entry.path, but the
		 * directory part of the path must be deduced from the subtree
		 * containing this entry. We assume here that the overall notes
		 * tree follows a strict byte-based progressive fanout
		 * structure (i.e. using 2/38, 2/2/36, etc. fanouts, and not
		 * e.g. 4/36 fanout). This means that if a non-note is found at
		 * path "dead/beef", the following code will register it as
		 * being found on "de/ad/beef".
		 * On the other hand, if you use such non-obvious non-note
		 * paths in the middle of a notes tree, you deserve what's
		 * coming to you ;). Note that for non-notes that are not
		 * SHA1-like at the top level, there will be no problems.
		 *
		 * To conclude, it is strongly advised to make sure non-notes
		 * have at least one non-hex character in the top-level path
		 * component.
		 */
		{
			struct strbuf non_note_path = STRBUF_INIT;
			const char *q = sha1_to_hex(subtree->key_sha1);
			int i;
			for (i = 0; i < prefix_len; i++) {
				strbuf_addch(&non_note_path, *q++);
				strbuf_addch(&non_note_path, *q++);
				strbuf_addch(&non_note_path, '/');
			}
			strbuf_addstr(&non_note_path, entry.path);
			add_non_note(t, strbuf_detach(&non_note_path, NULL),
				     entry.mode, entry.oid->hash);
		}
	}
	free(buf);
}