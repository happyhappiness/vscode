void setup_standard_excludes(struct dir_struct *dir)
{
	const char *path;

	dir->exclude_per_dir = ".gitignore";

	/* core.excludefile defaulting to $XDG_HOME/git/ignore */
	if (!excludes_file)
		excludes_file = xdg_config_home("ignore");
	if (excludes_file && !access_or_warn(excludes_file, R_OK, 0))
		add_excludes_from_file(dir, excludes_file);

	/* per repository user preference */
	path = git_path("info/exclude");
	if (!access_or_warn(path, R_OK, 0))
		add_excludes_from_file(dir, path);
}