static void note_tree_remove(struct notes_tree *t,
		struct int_node *tree, unsigned char n,
		struct leaf_node *entry)
{
	struct leaf_node *l;
	struct int_node *parent_stack[20];
	unsigned char i, j;
	void **p = note_tree_search(t, &tree, &n, entry->key_sha1);

	assert(GET_PTR_TYPE(entry) == 0); /* no type bits set */
	if (GET_PTR_TYPE(*p) != PTR_TYPE_NOTE)
		return; /* type mismatch, nothing to remove */
	l = (struct leaf_node *) CLR_PTR_TYPE(*p);
	if (hashcmp(l->key_sha1, entry->key_sha1))
		return; /* key mismatch, nothing to remove */

	/* we have found a matching entry */
	hashcpy(entry->val_sha1, l->val_sha1);
	free(l);
	*p = SET_PTR_TYPE(NULL, PTR_TYPE_NULL);

	/* consolidate this tree level, and parent levels, if possible */
	if (!n)
		return; /* cannot consolidate top level */
	/* first, build stack of ancestors between root and current node */
	parent_stack[0] = t->root;
	for (i = 0; i < n; i++) {
		j = GET_NIBBLE(i, entry->key_sha1);
		parent_stack[i + 1] = CLR_PTR_TYPE(parent_stack[i]->a[j]);
	}
	assert(i == n && parent_stack[i] == tree);
	/* next, unwind stack until note_tree_consolidate() is done */
	while (i > 0 &&
	       !note_tree_consolidate(parent_stack[i], parent_stack[i - 1],
				      GET_NIBBLE(i - 1, entry->key_sha1)))
		i--;
}