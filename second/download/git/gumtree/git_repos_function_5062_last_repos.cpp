static int need_to_gc(void)
{
	/*
	 * Setting gc.auto to 0 or negative can disable the
	 * automatic gc.
	 */
	if (gc_auto_threshold <= 0)
		return 0;

	/*
	 * If there are too many loose objects, but not too many
	 * packs, we run "repack -d -l".  If there are too many packs,
	 * we run "repack -A -d -l".  Otherwise we tell the caller
	 * there is no need.
	 */
	if (too_many_packs())
		add_repack_all_option();
	else if (too_many_loose_objects())
		add_repack_incremental_option();
	else
		return 0;

	if (run_hook_le(NULL, "pre-auto-gc", NULL))
		return 0;
	return 1;
}