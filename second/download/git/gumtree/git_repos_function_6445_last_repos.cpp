static int files_delete_reflog(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "delete_reflog");
	struct strbuf sb = STRBUF_INIT;
	int ret;

	files_reflog_path(refs, &sb, refname);
	ret = remove_path(sb.buf);
	strbuf_release(&sb);
	return ret;
}