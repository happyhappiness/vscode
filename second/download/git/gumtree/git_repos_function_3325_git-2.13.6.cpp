struct ref_iterator *refs_ref_iterator_begin(
		struct ref_store *refs,
		const char *prefix, int trim, int flags)
{
	struct ref_iterator *iter;

	iter = refs->be->iterator_begin(refs, prefix, flags);
	iter = prefix_ref_iterator_begin(iter, prefix, trim);

	return iter;
}