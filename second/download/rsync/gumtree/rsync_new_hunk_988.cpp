 * tweak any dest-relative paths to make them work for a dry-run (the
 * destination dir must be in curr_dir[] when this function is called).
 * We also warn about any arg that is non-existent or not a directory. */
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

/* This is only called by the sender. */
static void read_final_goodbye(int f_in, int f_out)
{
	int i, iflags, xlen;
	uchar fnamecmp_type;
	char xname[MAXPATHLEN];

	shutting_down = True;

	if (protocol_version < 29)
		i = read_int(f_in);
	else {
		i = read_ndx_and_attrs(f_in, f_out, &iflags, &fnamecmp_type, xname, &xlen);
		if (protocol_version >= 31 && i == NDX_DONE) {
			if (am_sender)
				write_ndx(f_out, NDX_DONE);
			else {
				if (batch_gen_fd >= 0) {
					while (read_int(batch_gen_fd) != NDX_DEL_STATS) {}
					read_del_stats(batch_gen_fd);
				}
				write_int(f_out, NDX_DONE);
			}
			i = read_ndx_and_attrs(f_in, f_out, &iflags, &fnamecmp_type, xname, &xlen);
		}
	}

	if (i != NDX_DONE) {
		rprintf(FERROR, "Invalid packet at end of run (%d) [%s]\n",
			i, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
