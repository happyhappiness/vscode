static int files_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct files_ref_iterator *iter =
		(struct files_ref_iterator *)ref_iterator;
	int ok;

	while ((ok = ref_iterator_advance(iter->iter0)) == ITER_OK) {
		if (iter->flags & DO_FOR_EACH_PER_WORKTREE_ONLY &&
		    ref_type(iter->iter0->refname) != REF_TYPE_PER_WORKTREE)
			continue;

		if (!(iter->flags & DO_FOR_EACH_INCLUDE_BROKEN) &&
		    !ref_resolves_to_object(iter->iter0->refname,
					    iter->iter0->oid,
					    iter->iter0->flags))
			continue;

		iter->base.refname = iter->iter0->refname;
		iter->base.oid = iter->iter0->oid;
		iter->base.flags = iter->iter0->flags;
		return ITER_OK;
	}

	iter->iter0 = NULL;
	if (ref_iterator_abort(ref_iterator) != ITER_DONE)
		ok = ITER_ERROR;

	return ok;
}