int is_inside_dir(const char *dir)
{
	char cwd[PATH_MAX];
	if (!dir)
		return 0;
	if (!getcwd(cwd, sizeof(cwd)))
		die_errno("can't find the current directory");
	return dir_inside_of(cwd, dir) >= 0;
}