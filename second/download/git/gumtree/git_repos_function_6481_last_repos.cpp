struct ref_iterator *merge_ref_iterator_begin(
		struct ref_iterator *iter0, struct ref_iterator *iter1,
		ref_iterator_select_fn *select, void *cb_data)
{
	struct merge_ref_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;

	/*
	 * We can't do the same kind of is_empty_ref_iterator()-style
	 * optimization here as overlay_ref_iterator_begin() does,
	 * because we don't know the semantics of the select function.
	 * It might, for example, implement "intersect" by passing
	 * references through only if they exist in both iterators.
	 */

	base_ref_iterator_init(ref_iterator, &merge_ref_iterator_vtable);
	iter->iter0 = iter0;
	iter->iter1 = iter1;
	iter->select = select;
	iter->cb_data = cb_data;
	iter->current = NULL;
	return ref_iterator;
}