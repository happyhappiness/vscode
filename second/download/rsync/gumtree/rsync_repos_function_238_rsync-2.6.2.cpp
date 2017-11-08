void finish_transfer(char *fname, char *fnametmp, struct file_struct *file)
{
	int ret;

	if (make_backups && !make_backup(fname))
		return;

	/* move tmp file over real file */
	ret = robust_rename(fnametmp, fname, file->mode & INITACCESSPERMS);
	if (ret < 0) {
		rprintf(FERROR, "%s %s -> \"%s\": %s\n",
		    ret == -2 ? "copy" : "rename",
		    full_fname(fnametmp), fname, strerror(errno));
		do_unlink(fnametmp);
	} else {
		set_perms(fname,file,NULL,0);
	}
}