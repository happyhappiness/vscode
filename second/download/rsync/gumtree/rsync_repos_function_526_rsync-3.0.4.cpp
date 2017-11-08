static void check_alt_basis_dirs(void)
{
	STRUCT_STAT st;
	char **dir_p, *slash = strrchr(curr_dir, '/');

	for (dir_p = basis_dir; *dir_p; dir_p++) {
		if (dry_run > 1 && **dir_p != '/') {
			int len = curr_dir_len + 1 + strlen(*dir_p) + 1;
			char *new = new_array(char, len);
			if (!new)
				out_of_memory("check_alt_basis_dirs");
			if (slash && strncmp(*dir_p, "../", 3) == 0) {
			    /* We want to remove only one leading "../" prefix for
			     * the directory we couldn't create in dry-run mode:
			     * this ensures that any other ".." references get
			     * evaluated the same as they would for a live copy. */
			    *slash = '\0';
			    pathjoin(new, len, curr_dir, *dir_p + 3);
			    *slash = '/';
			} else
			    pathjoin(new, len, curr_dir, *dir_p);
			*dir_p = new;
		}
		if (do_stat(*dir_p, &st) < 0) {
			rprintf(FWARNING, "%s arg does not exist: %s\n",
				dest_option, *dir_p);
		} else if (!S_ISDIR(st.st_mode)) {
			rprintf(FWARNING, "%s arg is not a dir: %s\n",
				dest_option, *dir_p);
		}
	}
}