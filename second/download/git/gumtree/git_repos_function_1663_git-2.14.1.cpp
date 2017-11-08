int diff_flush_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	int i;
	int result = diff_get_patch_id(options, oid, diff_header_only);

	for (i = 0; i < q->nr; i++)
		diff_free_filepair(q->queue[i]);

	free(q->queue);
	DIFF_QUEUE_CLEAR(q);

	return result;
}