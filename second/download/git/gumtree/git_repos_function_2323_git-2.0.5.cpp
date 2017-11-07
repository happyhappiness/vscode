void clear_prio_queue(struct prio_queue *queue)
{
	free(queue->array);
	queue->nr = 0;
	queue->alloc = 0;
	queue->array = NULL;
}