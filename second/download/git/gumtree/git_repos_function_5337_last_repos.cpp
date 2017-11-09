static void separate_git_dir(const char *git_dir, const char *git_link)
{
	struct stat st;

	if (!stat(git_link, &st)) {
		const char *src;

		if (S_ISREG(st.st_mode))
			src = read_gitfile(git_link);
		else if (S_ISDIR(st.st_mode))
			src = git_link;
		else
			die(_("unable to handle file type %d"), (int)st.st_mode);

		if (rename(src, git_dir))
			die_errno(_("unable to move %s to %s"), src, git_dir);
	}

	write_file(git_link, "gitdir: %s", git_dir);
}