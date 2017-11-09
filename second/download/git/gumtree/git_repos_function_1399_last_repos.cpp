static int checkout_target(struct index_state *istate,
			   struct cache_entry *ce, struct stat *st)
{
	struct checkout costate = CHECKOUT_INIT;

	costate.refresh_cache = 1;
	costate.istate = istate;
	if (checkout_entry(ce, &costate, NULL) || lstat(ce->name, st))
		return error(_("cannot checkout %s"), ce->name);
	return 0;
}