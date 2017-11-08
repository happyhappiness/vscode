const char *resolve_gitdir(const char *suspect)
{
	if (is_git_directory(suspect))
		return suspect;
	return read_gitfile(suspect);
}