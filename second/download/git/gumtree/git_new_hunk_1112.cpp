		string_list_clear(rejects, 0);
	}
	if (something_displayed)
		fprintf(stderr, _("Aborting\n"));
}

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

static void reload_gitmodules_file(struct index_state *index,
				   struct checkout *state)
{
	int i;
	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];
		if (ce->ce_flags & CE_UPDATE) {
			int r = strcmp(ce->name, ".gitmodules");
			if (r < 0)
				continue;
			else if (r == 0) {
				submodule_free();
				checkout_entry(ce, state, NULL);
				gitmodules_config();
				git_config(submodule_config, NULL);
			} else
				break;
		}
	}
}

/*
 * Unlink the last component and schedule the leading directories for
 * removal, such that empty directories get removed.
 */
static void unlink_entry(const struct cache_entry *ce)
{
	const struct submodule *sub = submodule_from_ce(ce);
	if (sub) {
		switch (sub->update_strategy.type) {
		case SM_UPDATE_UNSPECIFIED:
		case SM_UPDATE_CHECKOUT:
		case SM_UPDATE_REBASE:
		case SM_UPDATE_MERGE:
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
