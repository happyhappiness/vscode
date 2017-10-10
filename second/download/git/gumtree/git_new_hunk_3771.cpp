	if (!o->buffer_output)
		flush_output(o);
}

static void output_commit_title(struct merge_options *o, struct commit *commit)
{
	strbuf_addchars(&o->obuf, ' ', o->call_depth * 2);
	if (commit->util)
		strbuf_addf(&o->obuf, "virtual %s\n",
			merge_remote_util(commit)->name);
	else {
		strbuf_addf(&o->obuf, "%s ",
			find_unique_abbrev(commit->object.oid.hash,
				DEFAULT_ABBREV));
		if (parse_commit(commit) != 0)
			strbuf_addf(&o->obuf, _("(bad commit)\n"));
		else {
			const char *title;
			const char *msg = get_commit_buffer(commit, NULL);
			int len = find_commit_subject(msg, &title);
			if (len)
				strbuf_addf(&o->obuf, "%.*s\n", len, title);
			unuse_commit_buffer(commit, msg);
		}
	}
	flush_output(o);
}

static int add_cacheinfo(struct merge_options *o,
		unsigned int mode, const struct object_id *oid,
		const char *path, int stage, int refresh, int options)
{
	struct cache_entry *ce;
	int ret;

	ce = make_cache_entry(mode, oid ? oid->hash : null_sha1, path, stage, 0);
	if (!ce)
		return err(o, _("addinfo_cache failed for path '%s'"), path);

	ret = add_cache_entry(ce, options);
	if (refresh) {
		struct cache_entry *nce;

		nce = refresh_cache_entry(ce, CE_MATCH_REFRESH | CE_MATCH_IGNORE_MISSING);
