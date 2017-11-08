static struct ref_iterator *files_reflog_iterator_begin(struct ref_store *ref_store)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ,
			       "reflog_iterator_begin");
	struct files_reflog_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;
	struct strbuf sb = STRBUF_INIT;

	base_ref_iterator_init(ref_iterator, &files_reflog_iterator_vtable);
	files_reflog_path(refs, &sb, NULL);
	iter->dir_iterator = dir_iterator_begin(sb.buf);
	iter->ref_store = ref_store;
	strbuf_release(&sb);
	return ref_iterator;
}