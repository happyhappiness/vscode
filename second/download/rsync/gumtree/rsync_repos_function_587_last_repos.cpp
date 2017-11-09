static void check_alt_basis_dirs(void)
{
	STRUCT_STAT st;
	char *slash = strrchr(curr_dir, '/');
	int j;

	for (j = 0; j < basis_dir_cnt; j++) {
		char *bdir = basis_dir[j];
		int bd_len = strlen(bdir);
		if (bd_len > 1 && bdir[bd_len-1] == '/')
			bdir[--bd_len] = '\0';
		if (dry_run > 1 && *bdir != '/') {
			int len = curr_dir_len + 1 + bd_len + 1;
			char *new = new_array(char, len);
			if (!new)
				out_of_memory("check_alt_basis_dirs");
			if (slash && strncmp(bdir, "../", 3) == 0) {
			    /* We want to remove only one leading "../" prefix for
			     * the directory we couldn't create in dry-run mode:
			     * this ensures that any other ".." references get
			     * evaluated the same as they would for a live copy. */
			    *slash = '\0';
			    pathjoin(new, len, curr_dir, bdir + 3);
			    *slash = '/';
			} else
			    pathjoin(new, len, curr_dir, bdir);
			basis_dir[j] = bdir = new;
		}
		if (do_stat(bdir, &st) < 0)
			rprintf(FWARNING, "%s arg does not exist: %s\n", dest_option, bdir);
		else if (!S_ISDIR(st.st_mode))
			rprintf(FWARNING, "%s arg is not a dir: %s\n", dest_option, bdir);
	}
}