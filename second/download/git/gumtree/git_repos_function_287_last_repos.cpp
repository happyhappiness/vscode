static char *get_socket_path(void)
{
	struct stat sb;
	char *old_dir, *socket;
	old_dir = expand_user_path("~/.git-credential-cache", 0);
	if (old_dir && !stat(old_dir, &sb) && S_ISDIR(sb.st_mode))
		socket = xstrfmt("%s/socket", old_dir);
	else
		socket = xdg_cache_home("credential/socket");
	free(old_dir);
	return socket;
}