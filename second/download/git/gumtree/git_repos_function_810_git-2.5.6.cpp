void wt_status_get_state(struct wt_status_state *state,
			 int get_detached_from)
{
	struct stat st;
	unsigned char sha1[20];

	if (!stat(git_path("MERGE_HEAD"), &st)) {
		state->merge_in_progress = 1;
	} else if (!stat(git_path("rebase-apply"), &st)) {
		if (!stat(git_path("rebase-apply/applying"), &st)) {
			state->am_in_progress = 1;
			if (!stat(git_path("rebase-apply/patch"), &st) && !st.st_size)
				state->am_empty_patch = 1;
		} else {
			state->rebase_in_progress = 1;
			state->branch = read_and_strip_branch("rebase-apply/head-name");
			state->onto = read_and_strip_branch("rebase-apply/onto");
		}
	} else if (!stat(git_path("rebase-merge"), &st)) {
		if (!stat(git_path("rebase-merge/interactive"), &st))
			state->rebase_interactive_in_progress = 1;
		else
			state->rebase_in_progress = 1;
		state->branch = read_and_strip_branch("rebase-merge/head-name");
		state->onto = read_and_strip_branch("rebase-merge/onto");
	} else if (!stat(git_path("CHERRY_PICK_HEAD"), &st) &&
			!get_sha1("CHERRY_PICK_HEAD", sha1)) {
		state->cherry_pick_in_progress = 1;
		hashcpy(state->cherry_pick_head_sha1, sha1);
	}
	if (!stat(git_path("BISECT_LOG"), &st)) {
		state->bisect_in_progress = 1;
		state->branch = read_and_strip_branch("BISECT_START");
	}
	if (!stat(git_path("REVERT_HEAD"), &st) &&
	    !get_sha1("REVERT_HEAD", sha1)) {
		state->revert_in_progress = 1;
		hashcpy(state->revert_head_sha1, sha1);
	}

	if (get_detached_from)
		wt_status_get_detached_from(state);
}