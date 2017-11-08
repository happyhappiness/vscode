int pop_dir(char *dir)
{
	if (chdir(dir))
		return 0;

	curr_dir_len = strlcpy(curr_dir, dir, sizeof curr_dir);
	if (curr_dir_len >= sizeof curr_dir)
		curr_dir_len = sizeof curr_dir - 1;

	return 1;
}