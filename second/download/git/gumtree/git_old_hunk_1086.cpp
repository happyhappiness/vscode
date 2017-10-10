	struct replay_opts *opts, int subject_len, const char *subject)
{
	if (rename(rebase_path_squash_msg(), rebase_path_message()))
		return error(_("could not rename '%s' to '%s'"),
			rebase_path_squash_msg(), rebase_path_message());
	unlink(rebase_path_fixup_msg());
	unlink(git_path("MERGE_MSG"));
	if (copy_file(git_path("MERGE_MSG"), rebase_path_message(), 0666))
		return error(_("could not copy '%s' to '%s'"),
			     rebase_path_message(), git_path("MERGE_MSG"));
	return error_with_patch(commit, subject, subject_len, opts, 1, 0);
}

static int do_exec(const char *command_line)
{
	const char *child_argv[] = { NULL, NULL };
