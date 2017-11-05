static int prefix_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct prefix_ref_iterator *iter =
		(struct prefix_ref_iterator *)ref_iterator;
	int ok;

	while ((ok = ref_iterator_advance(iter->iter0)) == ITER_OK) {
		if (!starts_with(iter->iter0->refname, iter->prefix))
			continue;

		if (iter->trim) {
			/*
			 * It is nonsense to trim off characters that
			 * you haven't already checked for via a
			 * prefix check, whether via this
			 * `prefix_ref_iterator` or upstream in
			 * `iter0`). So if there wouldn't be at least
			 * one character left in the refname after
			 * trimming, report it as a bug:
			 */
			if (strlen(iter->iter0->refname) <= iter->trim)
				die("BUG: attempt to trim too many characters");
			iter->base.refname = iter->iter0->refname + iter->trim;
		} else {
			iter->base.refname = iter->iter0->refname;
		}

		iter->base.oid = iter->iter0->oid;
		iter->base.flags = iter->iter0->flags;
		return ITER_OK;
	}

	iter->iter0 = NULL;
	if (ref_iterator_abort(ref_iterator) != ITER_DONE)
		return ITER_ERROR;
	return ok;
}