static void add_verbose_info(struct strbuf *out, struct ref_item *item,
			     int verbose, int abbrev)
{
	struct strbuf subject = STRBUF_INIT, stat = STRBUF_INIT;
	const char *sub = _(" **** invalid ref ****");
	struct commit *commit = item->commit;

	if (!parse_commit(commit)) {
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &subject);
		sub = subject.buf;
	}

	if (item->kind == REF_LOCAL_BRANCH)
		fill_tracking_info(&stat, item->name, verbose > 1);

	strbuf_addf(out, " %s %s%s",
		find_unique_abbrev(item->commit->object.sha1, abbrev),
		stat.buf, sub);
	strbuf_release(&stat);
	strbuf_release(&subject);
}