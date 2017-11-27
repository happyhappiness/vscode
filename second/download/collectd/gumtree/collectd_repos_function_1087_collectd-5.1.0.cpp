static int swap_read (void) /* {{{ */
{
	int              mib[3];
	size_t           mib_len;
	struct xsw_usage sw_usage;
	size_t           sw_usage_len;

	mib_len = 2;
	mib[0]  = CTL_VM;
	mib[1]  = VM_SWAPUSAGE;

	sw_usage_len = sizeof (struct xsw_usage);

	if (sysctl (mib, mib_len, &sw_usage, &sw_usage_len, NULL, 0) != 0)
		return (-1);

	/* The returned values are bytes. */
	swap_submit_gauge (NULL, "used", (gauge_t) sw_usage.xsu_used);
	swap_submit_gauge (NULL, "free", (gauge_t) sw_usage.xsu_avail);

	return (0);
}