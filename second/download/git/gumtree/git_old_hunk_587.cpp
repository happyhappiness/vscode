	xch->ignore = 0;

	return xch;
}


static int is_blank_line(xrecord_t **recs, long ix, long flags)
{
	return xdl_blankline(recs[ix]->ptr, recs[ix]->size, flags);
}

static int recs_match(xrecord_t **recs, long ixs, long ix, long flags)
{
	return (recs[ixs]->ha == recs[ix]->ha &&
		xdl_recmatch(recs[ixs]->ptr, recs[ixs]->size,
			     recs[ix]->ptr, recs[ix]->size,
			     flags));
}

int xdl_change_compact(xdfile_t *xdf, xdfile_t *xdfo, long flags) {
	long ix, ixo, ixs, ixref, grpsiz, nrec = xdf->nrec;
	char *rchg = xdf->rchg, *rchgo = xdfo->rchg;
	unsigned int blank_lines;
	xrecord_t **recs = xdf->recs;

	/*
	 * This is the same of what GNU diff does. Move back and forward
	 * change groups for a consistent and pretty diff output. This also
	 * helps in finding joinable change groups and reduce the diff size.
	 */
	for (ix = ixo = 0;;) {
		/*
		 * Find the first changed line in the to-be-compacted file.
		 * We need to keep track of both indexes, so if we find a
		 * changed lines group on the other file, while scanning the
		 * to-be-compacted file, we need to skip it properly. Note
		 * that loops that are testing for changed lines on rchg* do
		 * not need index bounding since the array is prepared with
		 * a zero at position -1 and N.
		 */
		for (; ix < nrec && !rchg[ix]; ix++)
			while (rchgo[ixo++]);
		if (ix == nrec)
			break;

		/*
		 * Record the start of a changed-group in the to-be-compacted file
		 * and find the end of it, on both to-be-compacted and other file
		 * indexes (ix and ixo).
		 */
		ixs = ix;
		for (ix++; rchg[ix]; ix++);
		for (; rchgo[ixo]; ixo++);

		do {
			grpsiz = ix - ixs;
			blank_lines = 0;

			/*
			 * If the line before the current change group, is equal to
			 * the last line of the current change group, shift backward
			 * the group.
			 */
			while (ixs > 0 && recs_match(recs, ixs - 1, ix - 1, flags)) {
				rchg[--ixs] = 1;
				rchg[--ix] = 0;

				/*
				 * This change might have joined two change groups,
				 * so we try to take this scenario in account by moving
				 * the start index accordingly (and so the other-file
				 * end-of-group index).
				 */
				for (; rchg[ixs - 1]; ixs--);
				while (rchgo[--ixo]);
			}

			/*
			 * Record the end-of-group position in case we are matched
			 * with a group of changes in the other file (that is, the
			 * change record before the end-of-group index in the other
			 * file is set).
			 */
			ixref = rchgo[ixo - 1] ? ix: nrec;

			/*
			 * If the first line of the current change group, is equal to
			 * the line next of the current change group, shift forward
			 * the group.
			 */
			while (ix < nrec && recs_match(recs, ixs, ix, flags)) {
				blank_lines += is_blank_line(recs, ix, flags);

				rchg[ixs++] = 0;
				rchg[ix++] = 1;

				/*
				 * This change might have joined two change groups,
				 * so we try to take this scenario in account by moving
				 * the start index accordingly (and so the other-file
				 * end-of-group index). Keep tracking the reference
				 * index in case we are shifting together with a
				 * corresponding group of changes in the other file.
				 */
				for (; rchg[ix]; ix++);
				while (rchgo[++ixo])
					ixref = ix;
			}
		} while (grpsiz != ix - ixs);

		/*
		 * Try to move back the possibly merged group of changes, to match
		 * the recorded position in the other file.
		 */
		while (ixref < ix) {
			rchg[--ixs] = 1;
			rchg[--ix] = 0;
			while (rchgo[--ixo]);
		}

		/*
		 * If a group can be moved back and forth, see if there is a
		 * blank line in the moving space. If there is a blank line,
		 * make sure the last blank line is the end of the group.
		 *
		 * As we already shifted the group forward as far as possible
		 * in the earlier loop, we need to shift it back only if at all.
		 */
		if ((flags & XDF_COMPACTION_HEURISTIC) && blank_lines) {
			while (ixs > 0 &&
			       !is_blank_line(recs, ix - 1, flags) &&
			       recs_match(recs, ixs - 1, ix - 1, flags)) {
				rchg[--ixs] = 1;
				rchg[--ix] = 0;
			}
		}
	}

	return 0;
}


int xdl_build_script(xdfenv_t *xe, xdchange_t **xscr) {
	xdchange_t *cscr = NULL, *xch;
