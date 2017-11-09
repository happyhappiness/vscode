static int files_init_db(struct ref_store *ref_store, struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "init_db");
	struct strbuf sb = STRBUF_INIT;

	/*
	 * Create .git/refs/{heads,tags}
	 */
	files_ref_path(refs, &sb, "refs/heads");
	safe_create_dir(sb.buf, 1);

	strbuf_reset(&sb);
	files_ref_path(refs, &sb, "refs/tags");
	safe_create_dir(sb.buf, 1);

	strbuf_release(&sb);
	return 0;
}