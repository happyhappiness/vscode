			rprintf(FINFO,"%s is uptodate\n",fname);
	}
	return updated;
}


void sig_int(void)
{
	exit_cleanup(1);
}


/* finish off a file transfer, renaming the file and setting the permissions
   and ownership */
void finish_transfer(char *fname, char *fnametmp, struct file_struct *file)
{
	if (make_backups) {
		char fnamebak[MAXPATHLEN];
		if (strlen(fname) + strlen(backup_suffix) > (MAXPATHLEN-1)) {
			rprintf(FERROR,"backup filename too long\n");
			return;
