static int make_simple_backup(char *fname)
{
	char fnamebak[MAXPATHLEN];

	if (stringjoin(fnamebak, sizeof fnamebak, fname, backup_suffix, NULL)
	    >= sizeof fnamebak) {
		rprintf(FERROR, "backup filename too long\n");
		return 0;
	}

	if (do_rename(fname, fnamebak) != 0) {
		/* cygwin (at least version b19) reports EINVAL */
		if (errno != ENOENT && errno != EINVAL) {
			rsyserr(FERROR, errno, "rename %s to backup %s", fname, fnamebak);
			return 0;
		}
	} else if (verbose > 1) {
		rprintf(FINFO, "backed up %s to %s\n", fname, fnamebak);
	}
	return 1;
}