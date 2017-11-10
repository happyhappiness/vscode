static void diffcore_apply_filter(struct diff_options *options)
{
	int i;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;

	DIFF_QUEUE_CLEAR(&outq);

	if (!options->filter)
		return;

	if (filter_bit_tst(DIFF_STATUS_FILTER_AON, options)) {
		int found;
		for (i = found = 0; !found && i < q->nr; i++) {
			if (match_filter(options, q->queue[i]))
				found++;
		}
		if (found)
			return;

		/* otherwise we will clear the whole queue
		 * by copying the empty outq at the end of this
		 * function, but first clear the current entries
		 * in the queue.
		 */
		for (i = 0; i < q->nr; i++)
			diff_free_filepair(q->queue[i]);
	}
	else {
		/* Only the matching ones */
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (match_filter(options, p))
				diff_q(&outq, p);
			else
				diff_free_filepair(p);
		}
	}
	free(q->queue);
	*q = outq;
}