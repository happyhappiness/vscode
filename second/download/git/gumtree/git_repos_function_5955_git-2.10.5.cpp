struct ref_iterator *files_reflog_iterator_begin(void)
{
	struct files_reflog_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;

	base_ref_iterator_init(ref_iterator, &files_reflog_iterator_vtable);
	iter->dir_iterator = dir_iterator_begin(git_path("logs"));
	return ref_iterator;
}