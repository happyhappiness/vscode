		die(_("%s: Unable to write new index file"), action_name(opts));
	rollback_lock_file(&index_lock);

	if (opts->signoff)
		append_signoff(msgbuf, 0, 0);

	if (!clean) {
		int i;
		strbuf_addstr(msgbuf, "\nConflicts:\n");
		for (i = 0; i < active_nr;) {
			const struct cache_entry *ce = active_cache[i++];
			if (ce_stage(ce)) {
				strbuf_addch(msgbuf, '\t');
				strbuf_addstr(msgbuf, ce->name);
				strbuf_addch(msgbuf, '\n');
				while (i < active_nr && !strcmp(ce->name,
						active_cache[i]->name))
					i++;
			}
		}
	}

	return !clean;
}

static int is_index_unchanged(void)
{
