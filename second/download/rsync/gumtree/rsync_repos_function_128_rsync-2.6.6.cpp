static int make_simple_backup(char *fname)
{
	int rename_errno;
	char *fnamebak = get_backup_name(fname);

	if (!fnamebak)
		return 0;

	while (1) {
		if (do_rename(fname, fnamebak) == 0) {
			if (verbose > 1) {
				rprintf(FINFO, "backed up %s to %s\n",
					safe_fname(fname),
					safe_fname(fnamebak));
			}
			break;
		}
		/* cygwin (at least version b19) reports EINVAL */
		if (errno == ENOENT || errno == EINVAL)
			break;

		rename_errno = errno;
		if (errno == EISDIR && do_rmdir(fnamebak) == 0)
			continue;
		if (errno == ENOTDIR && do_unlink(fnamebak) == 0)
			continue;

		rsyserr(FERROR, rename_errno, "rename %s to backup %s",
			safe_fname(fname), safe_fname(fnamebak));
		errno = rename_errno;
		return 0;
	}

	return 1;
}