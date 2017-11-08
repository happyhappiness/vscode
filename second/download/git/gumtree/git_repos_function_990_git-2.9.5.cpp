static void merge_broken(struct diff_filepair *p,
			 struct diff_filepair *pp,
			 struct diff_queue_struct *outq)
{
	/* p and pp are broken pairs we want to merge */
	struct diff_filepair *c = p, *d = pp, *dp;
	if (DIFF_FILE_VALID(p->one)) {
		/* this must be a delete half */
		d = p; c = pp;
	}
	/* Sanity check */
	if (!DIFF_FILE_VALID(d->one))
		die("internal error in merge #1");
	if (DIFF_FILE_VALID(d->two))
		die("internal error in merge #2");
	if (DIFF_FILE_VALID(c->one))
		die("internal error in merge #3");
	if (!DIFF_FILE_VALID(c->two))
		die("internal error in merge #4");

	dp = diff_queue(outq, d->one, c->two);
	dp->score = p->score;
	/*
	 * We will be one extra user of the same src side of the
	 * broken pair, if it was used as the rename source for other
	 * paths elsewhere.  Increment to mark that the path stays
	 * in the resulting tree.
	 */
	d->one->rename_used++;
	diff_free_filespec_data(d->two);
	diff_free_filespec_data(c->one);
	free(d);
	free(c);
}