struct ref_iterator *overlay_ref_iterator_begin(
		struct ref_iterator *front, struct ref_iterator *back)
{
	/*
	 * Optimization: if one of the iterators is empty, return the
	 * other one rather than incurring the overhead of wrapping
	 * them.
	 */
	if (is_empty_ref_iterator(front)) {
		ref_iterator_abort(front);
		return back;
	} else if (is_empty_ref_iterator(back)) {
		ref_iterator_abort(back);
		return front;
	}

	return merge_ref_iterator_begin(front, back,
					overlay_iterator_select, NULL);
}