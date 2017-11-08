static void unlink_entry(const struct cache_entry *ce)
{
	if (!check_leading_path(ce->name, ce_namelen(ce)))
		return;
	if (remove_or_warn(ce->ce_mode, ce->name))
		return;
	schedule_dir_for_removal(ce->name, ce_namelen(ce));
}