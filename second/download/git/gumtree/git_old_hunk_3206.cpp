
static const char permissions_advice[] =
"The permissions on your socket directory are too loose; other\n"
"users may be able to read your cached credentials. Consider running:\n"
"\n"
"	chmod 0700 %s";
static void check_socket_directory(const char *path)
{
	struct stat st;
	char *path_copy = xstrdup(path);
	char *dir = dirname(path_copy);

	if (!stat(dir, &st)) {
		if (st.st_mode & 077)
			die(permissions_advice, dir);
		free(path_copy);
		return;
	}

	/*
	 * We must be sure to create the directory with the correct mode,
	 * not just chmod it after the fact; otherwise, there is a race
	 * condition in which somebody can chdir to it, sleep, then try to open
	 * our protected socket.
	 */
	if (safe_create_leading_directories_const(dir) < 0)
		die_errno("unable to create directories for '%s'", dir);
	if (mkdir(dir, 0700) < 0)
		die_errno("unable to mkdir '%s'", dir);
	free(path_copy);
}

int main(int argc, const char **argv)
{
	const char *socket_path;
