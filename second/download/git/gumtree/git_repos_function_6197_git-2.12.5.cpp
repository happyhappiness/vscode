static int files_for_each_reflog_ent(struct ref_store *ref_store,
				     const char *refname,
				     each_reflog_ent_fn fn, void *cb_data)
{
	FILE *logfp;
	struct strbuf sb = STRBUF_INIT;
	int ret = 0;

	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "for_each_reflog_ent");

	logfp = fopen(git_path("logs/%s", refname), "r");
	if (!logfp)
		return -1;

	while (!ret && !strbuf_getwholeline(&sb, logfp, '\n'))
		ret = show_one_reflog_ent(&sb, fn, cb_data);
	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}