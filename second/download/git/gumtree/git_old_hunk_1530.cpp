	int ok;

	while ((ok = ref_iterator_advance(iter->iter0)) == ITER_OK) {
		if (!starts_with(iter->iter0->refname, iter->prefix))
			continue;

		iter->base.refname = iter->iter0->refname + iter->trim;
		iter->base.oid = iter->iter0->oid;
		iter->base.flags = iter->iter0->flags;
		return ITER_OK;
	}

	iter->iter0 = NULL;
