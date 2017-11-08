void write_batch_argvs_file(int argc, char *argv[])
{
	int fdb;
	int i;
	char buff[256]; /* XXX */
	char buff2[MAXPATHLEN + 6];
	char filename[MAXPATHLEN];

	/* Set up file extension */
	strlcpy(filename, batch_prefix, sizeof(filename));
	strlcat(filename, rsync_argvs_file, sizeof(filename));

	/*
	 * Open batch argvs file for writing;
	 * create it if it doesn't exist
	 */
	fdb = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		      S_IREAD | S_IWRITE | S_IEXEC);
	if (fdb == -1) {
		rprintf(FERROR, "Batch file %s open error: %s\n",
			filename, strerror(errno));
		close(fdb);
		exit_cleanup(1);
	}
	buff[0] = '\0';

	/* Write argvs info to batch file */

	for (i = 0; i < argc; ++i) {
		if (i == argc - 2) /* Skip source directory on cmdline */
		    continue;
		/*
		 * FIXME:
		 * I think directly manipulating argv[] is probably bogus
		 */
		if (!strncmp(argv[i], "--write-batch",
			strlen("--write-batch"))) {
			/* Safer to change it here than script */
			/*
			 * Change to --read-batch=prefix
			 * to get ready for remote
			 */
			strlcat(buff, "--read-batch=", sizeof(buff));
			strlcat(buff, batch_prefix, sizeof(buff));
		} else
		if (i == argc - 1) {
		    snprintf(buff2, sizeof(buff2), "${1:-%s}", argv[i]);
		    strlcat(buff, buff2, sizeof(buff));
		}
		else {
			strlcat(buff, argv[i], sizeof(buff));
		}

		if (i < (argc - 1)) {
			strlcat(buff, " ", sizeof(buff));
		}
	}
	strlcat(buff, "\n", sizeof(buff));
	if (!write(fdb, buff, strlen(buff))) {
		rprintf(FERROR, "Batch file %s write error: %s\n",
			filename, strerror(errno));
		close(fdb);
		exit_cleanup(1);
	}
	close(fdb);
}