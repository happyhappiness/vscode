static int check_updates(struct unpack_trees_options *o)
{
	unsigned cnt = 0;
	int errs = 0;
	struct progress *progress = NULL;
	struct index_state *index = &o->result;
	struct checkout state = CHECKOUT_INIT;
	int i;

	state.force = 1;
	state.quiet = 1;
	state.refresh_cache = 1;
	state.istate = index;

	progress = get_progress(o);

	if (o->update)
		git_attr_set_direction(GIT_ATTR_CHECKOUT, index);
	for (i = 0; i < index->cache_nr; i++) {
		const struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_WT_REMOVE) {
			display_progress(progress, ++cnt);
			if (o->update && !o->dry_run)
				unlink_entry(ce);
		}
	}
	remove_marked_cache_entries(index);
	remove_scheduled_dirs();

	if (should_update_submodules() && o->update && !o->dry_run)
		reload_gitmodules_file(index, &state);

	enable_delayed_checkout(&state);
	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_UPDATE) {
			if (ce->ce_flags & CE_WT_REMOVE)
				die("BUG: both update and delete flags are set on %s",
				    ce->name);
			display_progress(progress, ++cnt);
			ce->ce_flags &= ~CE_UPDATE;
			if (o->update && !o->dry_run) {
				errs |= checkout_entry(ce, &state, NULL);
			}
		}
	}
	errs |= finish_delayed_checkout(&state);
	stop_progress(&progress);
	if (o->update)
		git_attr_set_direction(GIT_ATTR_CHECKIN, NULL);
	return errs != 0;
}