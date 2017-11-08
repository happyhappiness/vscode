static void am_abort(struct am_state *state)
{
	struct object_id curr_head, orig_head;
	int has_curr_head, has_orig_head;
	char *curr_branch;

	if (!safe_to_abort(state)) {
		am_destroy(state);
		return;
	}

	am_rerere_clear();

	curr_branch = resolve_refdup("HEAD", 0, curr_head.hash, NULL);
	has_curr_head = curr_branch && !is_null_oid(&curr_head);
	if (!has_curr_head)
		hashcpy(curr_head.hash, EMPTY_TREE_SHA1_BIN);

	has_orig_head = !get_oid("ORIG_HEAD", &orig_head);
	if (!has_orig_head)
		hashcpy(orig_head.hash, EMPTY_TREE_SHA1_BIN);

	clean_index(&curr_head, &orig_head);

	if (has_orig_head)
		update_ref_oid("am --abort", "HEAD", &orig_head,
				has_curr_head ? &curr_head : NULL, 0,
				UPDATE_REFS_DIE_ON_ERR);
	else if (curr_branch)
		delete_ref(NULL, curr_branch, NULL, REF_NODEREF);

	free(curr_branch);
	am_destroy(state);
}