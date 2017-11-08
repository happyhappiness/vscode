static int merge_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct merge_ref_iterator *iter =
		(struct merge_ref_iterator *)ref_iterator;
	int ok;

	if (!iter->current) {
		/* Initialize: advance both iterators to their first entries */
		if ((ok = ref_iterator_advance(iter->iter0)) != ITER_OK) {
			iter->iter0 = NULL;
			if (ok == ITER_ERROR)
				goto error;
		}
		if ((ok = ref_iterator_advance(iter->iter1)) != ITER_OK) {
			iter->iter1 = NULL;
			if (ok == ITER_ERROR)
				goto error;
		}
	} else {
		/*
		 * Advance the current iterator past the just-used
		 * entry:
		 */
		if ((ok = ref_iterator_advance(*iter->current)) != ITER_OK) {
			*iter->current = NULL;
			if (ok == ITER_ERROR)
				goto error;
		}
	}

	/* Loop until we find an entry that we can yield. */
	while (1) {
		struct ref_iterator **secondary;
		enum iterator_selection selection =
			iter->select(iter->iter0, iter->iter1, iter->cb_data);

		if (selection == ITER_SELECT_DONE) {
			return ref_iterator_abort(ref_iterator);
		} else if (selection == ITER_SELECT_ERROR) {
			ref_iterator_abort(ref_iterator);
			return ITER_ERROR;
		}

		if ((selection & ITER_CURRENT_SELECTION_MASK) == 0) {
			iter->current = &iter->iter0;
			secondary = &iter->iter1;
		} else {
			iter->current = &iter->iter1;
			secondary = &iter->iter0;
		}

		if (selection & ITER_SKIP_SECONDARY) {
			if ((ok = ref_iterator_advance(*secondary)) != ITER_OK) {
				*secondary = NULL;
				if (ok == ITER_ERROR)
					goto error;
			}
		}

		if (selection & ITER_YIELD_CURRENT) {
			iter->base.refname = (*iter->current)->refname;
			iter->base.oid = (*iter->current)->oid;
			iter->base.flags = (*iter->current)->flags;
			return ITER_OK;
		}
	}

error:
	ref_iterator_abort(ref_iterator);
	return ITER_ERROR;
}