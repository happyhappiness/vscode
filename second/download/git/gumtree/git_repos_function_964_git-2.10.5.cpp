void wt_status_get_state(struct wt_status_state *state,
			 int get_detached_from)
{
	struct stat st;
	unsigned char sha1[20];

	if (!stat(git_path_merge_head(), &st)) {
		state->merge_in_progress = 1;
	} else if (wt_status_check_rebase(NULL, state)) {
		;		/* all set */
	} else if (!stat(git_path_cherry_pick_head(), &st) &&
			!get_sha1("CHERRY_PICK_HEAD", sha1)) {
		state->cherry_pick_in_progress = 1;
		hashcpy(state->cherry_pick_head_sha1, sha1);
	}
	wt_status_check_bisect(NULL, state);
	if (!stat(git_path_revert_head(), &st) &&
	    !get_sha1("REVERT_HEAD", sha1)) {
		state->revert_in_progress = 1;
		hashcpy(state->revert_head_sha1, sha1);
	}

	if (get_detached_from)
		wt_status_get_detached_from(state);
}