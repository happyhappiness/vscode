const char *git_etc_gitconfig(void)
{
	static const char *system_wide;
	if (!system_wide)
		system_wide = system_path(ETC_GITCONFIG);
	return system_wide;
}