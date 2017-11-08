static void unlink_entry(const struct cache_entry *ce)
{
	const struct submodule *sub = submodule_from_ce(ce);
	if (sub) {
		switch (sub->update_strategy.type) {
		case SM_UPDATE_UNSPECIFIED:
		case SM_UPDATE_CHECKOUT:
		case SM_UPDATE_REBASE:
		case SM_UPDATE_MERGE:
			/* state.force is set at the caller. */
			submodule_move_head(ce->name, "HEAD", NULL,
					    SUBMODULE_MOVE_HEAD_FORCE);
			break;
		case SM_UPDATE_NONE:
		case SM_UPDATE_COMMAND:
			return; /* Do not touch the submodule. */
		}
	}
	if (!check_leading_path(ce->name, ce_namelen(ce)))
		return;
	if (remove_or_warn(ce->ce_mode, ce->name))
		return;
	schedule_dir_for_removal(ce->name, ce_namelen(ce));
}