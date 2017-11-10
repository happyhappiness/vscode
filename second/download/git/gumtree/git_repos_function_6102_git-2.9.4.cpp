int mingw_execvp(const char *cmd, char *const *argv)
{
	char **path = get_path_split();
	char *prog = path_lookup(cmd, path, 0);

	if (prog) {
		mingw_execv(prog, argv);
		free(prog);
	} else
		errno = ENOENT;

	free_path_split(path);
	return -1;
}