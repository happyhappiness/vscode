static void refresh_cache_or_die(int refresh_flags)
{
	/*
	 * refresh_flags contains REFRESH_QUIET, so the only errors
	 * are for unmerged entries.
	 */
	if (refresh_cache(refresh_flags | REFRESH_IN_PORCELAIN))
		die_resolve_conflict("commit");
}