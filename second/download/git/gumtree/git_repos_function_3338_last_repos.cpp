void clear_prio_queue(struct prio_queue *queue)
{
	FREE_AND_NULL(queue->array);
	queue->nr = 0;
	queue->alloc = 0;
	queue->insertion_ctr = 0;
}