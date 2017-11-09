void diffcore_merge_broken(void)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;
	int i, j;

	DIFF_QUEUE_CLEAR(&outq);

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!p)
			/* we already merged this with its peer */
			continue;
		else if (p->broken_pair &&
			 !strcmp(p->one->path, p->two->path)) {
			/* If the peer also survived rename/copy, then
			 * we merge them back together.
			 */
			for (j = i + 1; j < q->nr; j++) {
				struct diff_filepair *pp = q->queue[j];
				if (pp->broken_pair &&
				    !strcmp(pp->one->path, pp->two->path) &&
				    !strcmp(p->one->path, pp->two->path)) {
					/* Peer survived.  Merge them */
					merge_broken(p, pp, &outq);
					q->queue[j] = NULL;
					break;
				}
			}
			if (q->nr <= j)
				/* The peer did not survive, so we keep
				 * it in the output.
				 */
				diff_q(&outq, p);
		}
		else
			diff_q(&outq, p);
	}
	free(q->queue);
	*q = outq;

	return;
}