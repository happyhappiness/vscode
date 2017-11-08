int notes_cache_write(struct notes_cache *c)
{
	unsigned char tree_sha1[20];
	unsigned char commit_sha1[20];

	if (!c || !c->tree.initialized || !c->tree.ref || !*c->tree.ref)
		return -1;
	if (!c->tree.dirty)
		return 0;

	if (write_notes_tree(&c->tree, tree_sha1))
		return -1;
	if (commit_tree(c->validity, strlen(c->validity), tree_sha1, NULL,
			commit_sha1, NULL, NULL) < 0)
		return -1;
	if (update_ref("update notes cache", c->tree.ref, commit_sha1, NULL,
		       0, UPDATE_REFS_QUIET_ON_ERR) < 0)
		return -1;

	return 0;
}