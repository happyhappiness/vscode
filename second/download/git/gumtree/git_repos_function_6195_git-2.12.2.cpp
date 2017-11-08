static struct ref_iterator *files_reflog_iterator_begin(struct ref_store *ref_store)
{
	struct files_reflog_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;

	/* Check validity (but we don't need the result): */
	files_downcast(ref_store, 0, "reflog_iterator_begin");

	base_ref_iterator_init(ref_iterator, &files_reflog_iterator_vtable);
	iter->dir_iterator = dir_iterator_begin(git_path("logs"));
	return ref_iterator;
}