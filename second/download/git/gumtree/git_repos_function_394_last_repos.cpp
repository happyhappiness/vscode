static int clean_shared_index_files(const char *current_hex)
{
	struct dirent *de;
	DIR *dir = opendir(get_git_dir());

	if (!dir)
		return error_errno(_("unable to open git dir: %s"), get_git_dir());

	while ((de = readdir(dir)) != NULL) {
		const char *sha1_hex;
		const char *shared_index_path;
		if (!skip_prefix(de->d_name, "sharedindex.", &sha1_hex))
			continue;
		if (!strcmp(sha1_hex, current_hex))
			continue;
		shared_index_path = git_path("%s", de->d_name);
		if (should_delete_shared_index(shared_index_path) > 0 &&
		    unlink(shared_index_path))
			warning_errno(_("unable to unlink: %s"), shared_index_path);
	}
	closedir(dir);

	return 0;
}