static void add_verbose_info(struct strbuf *out, struct ref_array_item *item,
			     struct ref_filter *filter, const char *refname)
{
	struct strbuf subject = STRBUF_INIT, stat = STRBUF_INIT;
	const char *sub = _(" **** invalid ref ****");
	struct commit *commit = item->commit;

	if (!parse_commit(commit)) {
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &subject);
		sub = subject.buf;
	}

	if (item->kind == FILTER_REFS_BRANCHES)
		fill_tracking_info(&stat, refname, filter->verbose > 1);

	strbuf_addf(out, " %s %s%s",
		find_unique_abbrev(item->commit->object.oid.hash, filter->abbrev),
		stat.buf, sub);
	strbuf_release(&stat);
	strbuf_release(&subject);
}