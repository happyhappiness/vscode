static int check_stages(unsigned stages, const struct cache_entry *ce, int pos)
{
	unsigned seen = 0;
	const char *name = ce->name;

	while (pos < active_nr) {
		ce = active_cache[pos];
		if (strcmp(name, ce->name))
			break;
		seen |= (1 << ce_stage(ce));
		pos++;
	}
	if ((stages & seen) != stages)
		return error(_("path '%s' does not have all necessary versions"),
			     name);
	return 0;
}