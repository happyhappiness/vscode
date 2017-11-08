static int merge_ref_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	struct merge_ref_iterator *iter =
		(struct merge_ref_iterator *)ref_iterator;

	if (!iter->current) {
		die("BUG: peel called before advance for merge iterator");
	}
	return ref_iterator_peel(*iter->current, peeled);
}