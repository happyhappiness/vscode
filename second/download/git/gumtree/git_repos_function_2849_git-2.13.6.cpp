void append_conflicts_hint(struct strbuf *msgbuf)
{
	int i;

	strbuf_addch(msgbuf, '\n');
	strbuf_commented_addf(msgbuf, "Conflicts:\n");
	for (i = 0; i < active_nr;) {
		const struct cache_entry *ce = active_cache[i++];
		if (ce_stage(ce)) {
			strbuf_commented_addf(msgbuf, "\t%s\n", ce->name);
			while (i < active_nr && !strcmp(ce->name,
							active_cache[i]->name))
				i++;
		}
	}
}