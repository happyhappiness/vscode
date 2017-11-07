static int checkout_target(struct cache_entry *ce, struct stat *st)
{
	struct checkout costate;

	memset(&costate, 0, sizeof(costate));
	costate.base_dir = "";
	costate.refresh_cache = 1;
	if (checkout_entry(ce, &costate, NULL) || lstat(ce->name, st))
		return error(_("cannot checkout %s"), ce->name);
	return 0;
}