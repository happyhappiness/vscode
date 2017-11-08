static inline void swap(struct prio_queue *queue, int i, int j)
{
	struct prio_queue_entry tmp = queue->array[i];
	queue->array[i] = queue->array[j];
	queue->array[j] = tmp;
}