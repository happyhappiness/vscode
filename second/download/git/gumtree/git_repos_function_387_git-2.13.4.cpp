static int too_many_not_shared_entries(struct index_state *istate)
{
	int i, not_shared = 0;
	int max_split = git_config_get_max_percent_split_change();

	switch (max_split) {
	case -1:
		/* not or badly configured: use the default value */
		max_split = default_max_percent_split_change;
		break;
	case 0:
		return 1; /* 0% means always write a new shared index */
	case 100:
		return 0; /* 100% means never write a new shared index */
	default:
		break; /* just use the configured value */
	}

	/* Count not shared entries */
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		if (!ce->index)
			not_shared++;
	}

	return (int64_t)istate->cache_nr * max_split < (int64_t)not_shared * 100;
}