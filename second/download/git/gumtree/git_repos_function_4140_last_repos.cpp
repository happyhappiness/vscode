void diffcore_order(const char *orderfile)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct obj_order *o;
	int i;

	if (!q->nr)
		return;

	ALLOC_ARRAY(o, q->nr);
	for (i = 0; i < q->nr; i++)
		o[i].obj = q->queue[i];
	order_objects(orderfile, pair_pathtwo, o, q->nr);
	for (i = 0; i < q->nr; i++)
		q->queue[i] = o[i].obj;
	free(o);
	return;
}