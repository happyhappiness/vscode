static int swap_read (void) /* {{{ */
{
	if (report_by_device)
		swap_read_separate ();
	else
		swap_read_combined ();

	swap_read_io ();

	return (0);
}