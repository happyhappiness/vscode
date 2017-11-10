void create_notes_commit(struct notes_tree *t, struct commit_list *parents,
			 const char *msg, size_t msg_len,
			 unsigned char *result_sha1)
{
	struct object_id tree_oid;

	assert(t->initialized);

	if (write_notes_tree(t, tree_oid.hash))
		die("Failed to write notes tree to database");

	if (!parents) {
		/* Deduce parent commit from t->ref */
		struct object_id parent_oid;
		if (!read_ref(t->ref, parent_oid.hash)) {
			struct commit *parent = lookup_commit(&parent_oid);
			if (parse_commit(parent))
				die("Failed to find/parse commit %s", t->ref);
			commit_list_insert(parent, &parents);
		}
		/* else: t->ref points to nothing, assume root/orphan commit */
	}

	if (commit_tree(msg, msg_len, tree_oid.hash, parents, result_sha1, NULL, NULL))
		die("Failed to commit notes tree to database");
}