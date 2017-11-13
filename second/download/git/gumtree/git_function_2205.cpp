static int create_seq_dir(void)
{
	const char *seq_dir = git_path(SEQ_DIR);

	if (file_exists(seq_dir)) {
		error(_("a cherry-pick or revert is already in progress"));
		advise(_("try \"git cherry-pick (--continue | --quit | --abort)\""));
		return -1;
	}
	else if (mkdir(seq_dir, 0777) < 0)
		die_errno(_("Could not create sequencer directory %s"), seq_dir);
	return 0;
}