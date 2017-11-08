int gitmkstemps(char *pattern, int suffix_len)
{
	return git_mkstemps_mode(pattern, suffix_len, 0600);
}