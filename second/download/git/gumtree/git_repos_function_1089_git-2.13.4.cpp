void diffcore_break(int break_score)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;

	/* When the filepair has this much edit (insert and delete),
	 * it is first considered to be a rewrite and broken into a
	 * create and delete filepair.  This is to help breaking a
	 * file that had too much new stuff added, possibly from
	 * moving contents from another file, so that rename/copy can
	 * match it with the other file.
	 *
	 * int break_score; we reuse incoming parameter for this.
	 */

	/* After a pair is broken according to break_score and
	 * subjected to rename/copy, both of them may survive intact,
	 * due to lack of suitable rename/copy peer.  Or, the caller
	 * may be calling us without using rename/copy.  When that
	 * happens, we merge the broken pieces back into one
	 * modification together if the pair did not have more than
	 * this much delete.  For this computation, we do not take
	 * insert into account at all.  If you start from a 100-line
	 * file and delete 97 lines of it, it does not matter if you
	 * add 27 lines to it to make a new 30-line file or if you add
	 * 997 lines to it to make a 1000-line file.  Either way what
	 * you did was a rewrite of 97%.  On the other hand, if you
	 * delete 3 lines, keeping 97 lines intact, it does not matter
	 * if you add 3 lines to it to make a new 100-line file or if
	 * you add 903 lines to it to make a new 1000-line file.
	 * Either way you did a lot of additions and not a rewrite.
	 * This merge happens to catch the latter case.  A merge_score
	 * of 80% would be a good default value (a broken pair that
	 * has score lower than merge_score will be merged back
	 * together).
	 */
	int merge_score;
	int i;

	/* See comment on DEFAULT_BREAK_SCORE and
	 * DEFAULT_MERGE_SCORE in diffcore.h
	 */
	merge_score = (break_score >> 16) & 0xFFFF;
	break_score = (break_score & 0xFFFF);

	if (!break_score)
		break_score = DEFAULT_BREAK_SCORE;
	if (!merge_score)
		merge_score = DEFAULT_MERGE_SCORE;

	DIFF_QUEUE_CLEAR(&outq);

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		int score;

		/*
		 * We deal only with in-place edit of blobs.
		 * We do not break anything else.
		 */
		if (DIFF_FILE_VALID(p->one) && DIFF_FILE_VALID(p->two) &&
		    object_type(p->one->mode) == OBJ_BLOB &&
		    object_type(p->two->mode) == OBJ_BLOB &&
		    !strcmp(p->one->path, p->two->path)) {
			if (should_break(p->one, p->two,
					 break_score, &score)) {
				/* Split this into delete and create */
				struct diff_filespec *null_one, *null_two;
				struct diff_filepair *dp;

				/* Set score to 0 for the pair that
				 * needs to be merged back together
				 * should they survive rename/copy.
				 * Also we do not want to break very
				 * small files.
				 */
				if (score < merge_score)
					score = 0;

				/* deletion of one */
				null_one = alloc_filespec(p->one->path);
				dp = diff_queue(&outq, p->one, null_one);
				dp->score = score;
				dp->broken_pair = 1;

				/* creation of two */
				null_two = alloc_filespec(p->two->path);
				dp = diff_queue(&outq, null_two, p->two);
				dp->score = score;
				dp->broken_pair = 1;

				diff_free_filespec_blob(p->one);
				diff_free_filespec_blob(p->two);
				free(p); /* not diff_free_filepair(), we are
					  * reusing one and two here.
					  */
				continue;
			}
		}
		diff_free_filespec_data(p->one);
		diff_free_filespec_data(p->two);
		diff_q(&outq, p);
	}
	free(q->queue);
	*q = outq;

	return;
}