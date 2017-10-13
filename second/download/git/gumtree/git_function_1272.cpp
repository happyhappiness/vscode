static void show_submodule(struct repository *superproject,
			   struct dir_struct *dir, const char *path)
{
	struct repository submodule;

	if (repo_submodule_init(&submodule, superproject, path))
		return;

	if (repo_read_index(&submodule) < 0)
		die("index file corrupt");

	repo_read_gitmodules(&submodule);

	show_files(&submodule, dir);

	repo_clear(&submodule);
}