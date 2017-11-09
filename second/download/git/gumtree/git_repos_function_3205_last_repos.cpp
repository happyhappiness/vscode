static struct progress *get_progress(struct unpack_trees_options *o)
{
	unsigned cnt = 0, total = 0;
	struct index_state *index = &o->result;

	if (!o->update || !o->verbose_update)
		return NULL;

	for (; cnt < index->cache_nr; cnt++) {
		const struct cache_entry *ce = index->cache[cnt];
		if (ce->ce_flags & (CE_UPDATE | CE_WT_REMOVE))
			total++;
	}

	return start_progress_delay(_("Checking out files"),
				    total, 50, 1);
}