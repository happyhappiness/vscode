static int swap_read (void) /* {{{ */
{
	struct kvm_swap data_s;
	int             status;

	derive_t used;
	derive_t free;
	derive_t total;

	if (kvm_obj == NULL)
		return (-1);

	/* only one structure => only get the grand total, no details */
	status = kvm_getswapinfo (kvm_obj, &data_s, 1, 0);
	if (status == -1)
		return (-1);

	total = (derive_t) data_s.ksw_total;
	used  = (derive_t) data_s.ksw_used;

	total *= (derive_t) kvm_pagesize;
	used  *= (derive_t) kvm_pagesize;

	free = total - used;

	swap_submit_gauge (NULL, "used", (gauge_t) used);
	swap_submit_gauge (NULL, "free", (gauge_t) free);

	return (0);
}