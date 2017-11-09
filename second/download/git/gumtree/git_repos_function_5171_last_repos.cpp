static int check_stage(int stage, const struct cache_entry *ce, int pos)
{
	while (pos < active_nr &&
	       !strcmp(active_cache[pos]->name, ce->name)) {
		if (ce_stage(active_cache[pos]) == stage)
			return 0;
		pos++;
	}
	if (stage == 2)
		return error(_("path '%s' does not have our version"), ce->name);
	else
		return error(_("path '%s' does not have their version"), ce->name);
}