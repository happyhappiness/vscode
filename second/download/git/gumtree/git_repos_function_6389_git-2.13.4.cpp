static enum iterator_selection overlay_iterator_select(
		struct ref_iterator *front, struct ref_iterator *back,
		void *cb_data)
{
	int cmp;

	if (!back)
		return front ? ITER_SELECT_0 : ITER_SELECT_DONE;
	else if (!front)
		return ITER_SELECT_1;

	cmp = strcmp(front->refname, back->refname);

	if (cmp < 0)
		return ITER_SELECT_0;
	else if (cmp > 0)
		return ITER_SELECT_1;
	else
		return ITER_SELECT_0_SKIP_1;
}