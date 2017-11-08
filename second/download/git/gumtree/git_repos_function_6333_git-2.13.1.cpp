static int files_reflog_exists(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "reflog_exists");
	struct strbuf sb = STRBUF_INIT;
	struct stat st;
	int ret;

	files_reflog_path(refs, &sb, refname);
	ret = !lstat(sb.buf, &st) && S_ISREG(st.st_mode);
	strbuf_release(&sb);
	return ret;
}