static void fix_basis_dirs(void)
{
	char **dir, *new, *slash;
	int len;

	if (dry_run <= 1)
		return;

	slash = strrchr(curr_dir, '/');

	for (dir = basis_dir; *dir; dir++) {
		if (**dir == '/')
			continue;
		len = curr_dir_len + 1 + strlen(*dir) + 1;
		if (!(new = new_array(char, len)))
			out_of_memory("fix_basis_dirs");
		if (slash && strncmp(*dir, "../", 3) == 0) {
		    /* We want to remove only one leading "../" prefix for
		     * the directory we couldn't create in dry-run mode:
		     * this ensures that any other ".." references get
		     * evaluated the same as they would for a live copy. */
		    *slash = '\0';
		    pathjoin(new, len, curr_dir, *dir + 3);
		    *slash = '/';
		} else
		    pathjoin(new, len, curr_dir, *dir);
		*dir = new;
	}
}