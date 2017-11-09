static void determine_whence(struct wt_status *s)
{
	if (file_exists(git_path_merge_head()))
		whence = FROM_MERGE;
	else if (file_exists(git_path_cherry_pick_head())) {
		whence = FROM_CHERRY_PICK;
		if (file_exists(git_path_seq_dir()))
			sequencer_in_use = 1;
	}
	else
		whence = FROM_COMMIT;
	if (s)
		s->whence = whence;
}