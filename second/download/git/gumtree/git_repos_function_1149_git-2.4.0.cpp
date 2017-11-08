void diffcore_fix_diff_index(struct diff_options *options)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	qsort(q->queue, q->nr, sizeof(q->queue[0]), diffnamecmp);
}