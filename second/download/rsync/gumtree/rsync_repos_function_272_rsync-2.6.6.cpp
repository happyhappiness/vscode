void finish_transfer(char *fname, char *fnametmp, struct file_struct *file,
		     int ok_to_set_time, int overwriting_basis)
{
	int ret;

	if (inplace) {
		if (verbose > 2)
			rprintf(FINFO, "finishing %s\n", safe_fname(fname));
		goto do_set_perms;
	}

	if (make_backups && overwriting_basis && !make_backup(fname))
		return;

	/* Change permissions before putting the file into place. */
	set_perms(fnametmp, file, NULL, ok_to_set_time ? 0 : PERMS_SKIP_MTIME);

	/* move tmp file over real file */
	if (verbose > 2) {
		rprintf(FINFO, "renaming %s to %s\n",
			safe_fname(fnametmp), safe_fname(fname));
	}
	ret = robust_rename(fnametmp, fname, file->mode & INITACCESSPERMS);
	if (ret < 0) {
		rsyserr(FERROR, errno, "%s %s -> \"%s\"",
		    ret == -2 ? "copy" : "rename",
		    full_fname(fnametmp), safe_fname(fname));
		do_unlink(fnametmp);
		return;
	}
	if (ret == 0) {
		/* The file was moved into place (not copied), so it's done. */
		return;
	}
    do_set_perms:
	set_perms(fname, file, NULL, ok_to_set_time ? 0 : PERMS_SKIP_MTIME);
}