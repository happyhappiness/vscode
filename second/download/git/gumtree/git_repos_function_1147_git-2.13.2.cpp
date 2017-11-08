static int dotdot_missing(const char *arg, char *dotdot,
			  struct rev_info *revs, int symmetric)
{
	if (revs->ignore_missing)
		return 0;
	/* de-munge so we report the full argument */
	*dotdot = '.';
	die(symmetric
	    ? "Invalid symmetric difference expression %s"
	    : "Invalid revision range %s", arg);
}