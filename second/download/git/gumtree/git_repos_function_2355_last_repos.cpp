static const char *git_etc_gitattributes(void)
{
	static const char *system_wide;
	if (!system_wide)
		system_wide = system_path(ETC_GITATTRIBUTES);
	return system_wide;
}