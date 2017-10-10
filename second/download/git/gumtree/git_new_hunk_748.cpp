static int create_seq_dir(void)
{
	if (file_exists(git_path_seq_dir())) {
		error(_("a cherry-pick or revert is already in progress"));
		advise(_("try \"git cherry-pick (--continue | --quit | --abort)\""));
		return -1;
	} else if (mkdir(git_path_seq_dir(), 0777) < 0)
		return error_errno(_("could not create sequencer directory '%s'"),
				   git_path_seq_dir());
	return 0;
}

static int save_head(const char *head)
