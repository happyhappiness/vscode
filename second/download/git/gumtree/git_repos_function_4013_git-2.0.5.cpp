static void determine_whence(struct wt_status *s)
{
	if (file_exists(git_path("MERGE_HEAD")))
		whence = FROM_MERGE;
	else if (file_exists(git_path("CHERRY_PICK_HEAD"))) {
		whence = FROM_CHERRY_PICK;
		if (file_exists(git_path("sequencer")))
			sequencer_in_use = 1;
	}
	else
		whence = FROM_COMMIT;
	if (s)
		s->whence = whence;
}