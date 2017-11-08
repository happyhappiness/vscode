int pop_dir(char *dir)
{
	if (chdir(dir))
		return 0;

	curr_dir_len = strlcpy(curr_dir, dir, sizeof curr_dir);
	if (curr_dir_len >= sizeof curr_dir)
		curr_dir_len = sizeof curr_dir - 1;
	if (sanitize_paths)
		curr_dir_depth = count_dir_elements(curr_dir + module_dirlen);

	return 1;
}