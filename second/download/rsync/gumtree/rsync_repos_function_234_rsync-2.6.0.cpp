void finish_transfer(char *fname, char *fnametmp, struct file_struct *file)
{
	if (make_backups && !make_backup(fname))
		return;

	/* move tmp file over real file */
	if (robust_rename(fnametmp,fname) != 0) {
		if (errno == EXDEV) {
			/* rename failed on cross-filesystem link.
			   Copy the file instead. */
			if (copy_file(fnametmp,fname, file->mode & INITACCESSPERMS)) {
				rprintf(FERROR, "copy %s -> \"%s\": %s\n",
					full_fname(fnametmp), fname,
					strerror(errno));
			} else {
				set_perms(fname,file,NULL,0);
			}
		} else {
			rprintf(FERROR,"rename %s -> \"%s\": %s\n",
				full_fname(fnametmp), fname, strerror(errno));
		}
		do_unlink(fnametmp);
	} else {
		set_perms(fname,file,NULL,0);
	}
}