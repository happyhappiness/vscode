static int swap_read (void) /* {{{ */
{
	sg_swap_stats *swap;

	swap = sg_get_swap_stats ();

	if (swap == NULL)
		return (-1);

	swap_submit ("used", (derive_t) swap->used, DS_TYPE_GAUGE);
	swap_submit ("free", (derive_t) swap->free, DS_TYPE_GAUGE);

	return (0);
}