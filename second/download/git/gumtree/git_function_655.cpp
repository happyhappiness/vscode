static int error_with_patch(struct commit *commit,
	const char *subject, int subject_len,
	struct replay_opts *opts, int exit_code, int to_amend)
{
	if (make_patch(commit, opts))
		return -1;

	if (to_amend) {
		if (intend_to_amend())
			return -1;

		fprintf(stderr, "You can amend the commit now, with\n"
			"\n"
			"  git commit --amend %s\n"
			"\n"
			"Once you are satisfied with your changes, run\n"
			"\n"
			"  git rebase --continue\n", gpg_sign_opt_quoted(opts));
	} else if (exit_code)
		fprintf(stderr, "Could not apply %s... %.*s\n",
			short_commit_name(commit), subject_len, subject);

	return exit_code;
}