static int swap_read (void) /* {{{ */
{
	sg_swap_stats *swap;

	swap = sg_get_swap_stats ();

	if (swap == NULL)
		return (-1);

	swap_submit_gauge (NULL, "used", (gauge_t) swap->used);
	swap_submit_gauge (NULL, "free", (gauge_t) swap->free);

	return (0);
}