static int check_submodule_move_head(const struct cache_entry *ce,
				     const char *old_id,
				     const char *new_id,
				     struct unpack_trees_options *o)
{
	const struct submodule *sub = submodule_from_ce(ce);
	if (!sub)
		return 0;

	switch (sub->update_strategy.type) {
	case SM_UPDATE_UNSPECIFIED:
	case SM_UPDATE_CHECKOUT:
		if (submodule_move_head(ce->name, old_id, new_id, SUBMODULE_MOVE_HEAD_DRY_RUN))
			return o->gently ? -1 :
				add_rejected_path(o, ERROR_WOULD_LOSE_SUBMODULE, ce->name);
		return 0;
	case SM_UPDATE_NONE:
		return 0;
	case SM_UPDATE_REBASE:
	case SM_UPDATE_MERGE:
	case SM_UPDATE_COMMAND:
	default:
		warning(_("submodule update strategy not supported for submodule '%s'"), ce->name);
		return -1;
	}
}