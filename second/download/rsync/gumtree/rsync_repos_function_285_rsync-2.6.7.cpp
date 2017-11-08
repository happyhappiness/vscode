void finish_transfer(char *fname, char *fnametmp, char *partialptr,
		     struct file_struct *file, int ok_to_set_time,
		     int overwriting_basis)
{
	int ret;

	if (inplace) {
		if (verbose > 2)
			rprintf(FINFO, "finishing %s\n", fname);
		fnametmp = fname;
		goto do_set_file_attrs;
	}

	if (make_backups && overwriting_basis && !make_backup(fname))
		return;

	/* Change permissions before putting the file into place. */
	set_file_attrs(fnametmp, file, NULL,
		       ok_to_set_time ? 0 : ATTRS_SKIP_MTIME);

	/* move tmp file over real file */
	if (verbose > 2)
		rprintf(FINFO, "renaming %s to %s\n", fnametmp, fname);
	ret = robust_rename(fnametmp, fname, partialptr,
			    file->mode & INITACCESSPERMS);
	if (ret < 0) {
		rsyserr(FERROR, errno, "%s %s -> \"%s\"",
			ret == -2 ? "copy" : "rename",
			full_fname(fnametmp), fname);
		do_unlink(fnametmp);
		return;
	}
	if (ret == 0) {
		/* The file was moved into place (not copied), so it's done. */
		return;
	}
	/* The file was copied, so tweak the perms of the copied file.  If it
	 * was copied to partialptr, move it into its final destination. */
	fnametmp = partialptr ? partialptr : fname;

  do_set_file_attrs:
	set_file_attrs(fnametmp, file, NULL,
		       ok_to_set_time ? 0 : ATTRS_SKIP_MTIME);

	if (partialptr) {
		if (do_rename(fnametmp, fname) < 0) {
			rsyserr(FERROR, errno, "rename %s -> \"%s\"",
				full_fname(fnametmp), fname);
		} else
			handle_partial_dir(partialptr, PDIR_DELETE);
	}
}