static int start_delete_delay_temp(void)
{
	char fnametmp[MAXPATHLEN];
	int save_dry_run = dry_run;

	dry_run = 0;
	if (!get_tmpname(fnametmp, "deldelay", False)
	 || (deldelay_fd = do_mkstemp(fnametmp, 0600)) < 0) {
		rprintf(FINFO, "NOTE: Unable to create delete-delay temp file%s.\n",
			inc_recurse ? "" : " -- switching to --delete-after");
		delete_during = 0;
		delete_after = !inc_recurse;
		dry_run = save_dry_run;
		return 0;
	}
	unlink(fnametmp);
	dry_run = save_dry_run;
	return 1;
}