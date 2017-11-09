static inline void swap(struct prio_queue *queue, int i, int j)
{
	SWAP(queue->array[i], queue->array[j]);
}