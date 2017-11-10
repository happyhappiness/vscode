static void warn_multiple_config(const unsigned char *commit_sha1,
				 const char *name, const char *option)
{
	const char *commit_string = "WORKTREE";
	if (commit_sha1)
		commit_string = sha1_to_hex(commit_sha1);
	warning("%s:.gitmodules, multiple configurations found for "
			"'submodule.%s.%s'. Skipping second one!",
			commit_string, name, option);
}