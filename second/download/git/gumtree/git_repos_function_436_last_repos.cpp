int notes_cache_write(struct notes_cache *c)
{
	struct object_id tree_oid, commit_oid;

	if (!c || !c->tree.initialized || !c->tree.update_ref ||
	    !*c->tree.update_ref)
		return -1;
	if (!c->tree.dirty)
		return 0;

	if (write_notes_tree(&c->tree, tree_oid.hash))
		return -1;
	if (commit_tree(c->validity, strlen(c->validity), tree_oid.hash, NULL,
			commit_oid.hash, NULL, NULL) < 0)
		return -1;
	if (update_ref("update notes cache", c->tree.update_ref, commit_oid.hash,
		       NULL, 0, UPDATE_REFS_QUIET_ON_ERR) < 0)
		return -1;

	return 0;
}