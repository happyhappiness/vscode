void home_config_paths(char **global, char **xdg, char *file)
{
	char *xdg_home = getenv("XDG_CONFIG_HOME");
	char *home = getenv("HOME");
	char *to_free = NULL;

	if (!home) {
		if (global)
			*global = NULL;
	} else {
		if (!xdg_home) {
			to_free = mkpathdup("%s/.config", home);
			xdg_home = to_free;
		}
		if (global)
			*global = mkpathdup("%s/.gitconfig", home);
	}

	if (xdg) {
		if (!xdg_home)
			*xdg = NULL;
		else
			*xdg = mkpathdup("%s/git/%s", xdg_home, file);
	}

	free(to_free);
}