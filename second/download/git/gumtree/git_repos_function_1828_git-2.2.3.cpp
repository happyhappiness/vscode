void setup_standard_excludes(struct dir_struct *dir)
{
	const char *path;
	char *xdg_path;

	dir->exclude_per_dir = ".gitignore";
	path = git_path("info/exclude");
	if (!excludes_file) {
		home_config_paths(NULL, &xdg_path, "ignore");
		excludes_file = xdg_path;
	}
	if (!access_or_warn(path, R_OK, 0))
		add_excludes_from_file(dir, path);
	if (excludes_file && !access_or_warn(excludes_file, R_OK, 0))
		add_excludes_from_file(dir, excludes_file);
}