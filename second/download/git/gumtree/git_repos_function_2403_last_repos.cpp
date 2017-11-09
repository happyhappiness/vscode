const char *resolve_gitdir_gently(const char *suspect, int *return_error_code)
{
	if (is_git_directory(suspect))
		return suspect;
	return read_gitfile_gently(suspect, return_error_code);
}