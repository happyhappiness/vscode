static int files_create_reflog(struct ref_store *ref_store,
			       const char *refname, int force_create,
			       struct strbuf *err)
{
	int ret;
	struct strbuf sb = STRBUF_INIT;

	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "create_reflog");

	ret = log_ref_setup(refname, &sb, err, force_create);
	strbuf_release(&sb);
	return ret;
}