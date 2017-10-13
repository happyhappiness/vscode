static int files_reflog_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct files_reflog_iterator *iter =
		(struct files_reflog_iterator *)ref_iterator;
	struct dir_iterator *diter = iter->dir_iterator;
	int ok;

	while ((ok = dir_iterator_advance(diter)) == ITER_OK) {
		int flags;

		if (!S_ISREG(diter->st.st_mode))
			continue;
		if (diter->basename[0] == '.')
			continue;
		if (ends_with(diter->basename, ".lock"))
			continue;

		if (read_ref_full(diter->relative_path, 0,
				  iter->oid.hash, &flags)) {
			error("bad ref for %s", diter->path.buf);
			continue;
		}

		iter->base.refname = diter->relative_path;
		iter->base.oid = &iter->oid;
		iter->base.flags = flags;
		return ITER_OK;
	}

	iter->dir_iterator = NULL;
	if (ref_iterator_abort(ref_iterator) == ITER_ERROR)
		ok = ITER_ERROR;
	return ok;
}