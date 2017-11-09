static void cd_to_homedir(void)
{
	const char *home = getenv("HOME");
	if (!home)
		die("could not determine user's home directory; HOME is unset");
	if (chdir(home) == -1)
		die("could not chdir to user's home directory");
}