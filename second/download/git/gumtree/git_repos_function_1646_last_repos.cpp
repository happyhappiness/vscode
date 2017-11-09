void diff_q(struct diff_queue_struct *queue, struct diff_filepair *dp)
{
	ALLOC_GROW(queue->queue, queue->nr + 1, queue->alloc);
	queue->queue[queue->nr++] = dp;
}