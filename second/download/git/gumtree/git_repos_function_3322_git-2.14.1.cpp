static inline int compare(struct prio_queue *queue, int i, int j)
{
	int cmp = queue->compare(queue->array[i].data, queue->array[j].data,
				 queue->cb_data);
	if (!cmp)
		cmp = queue->array[i].ctr - queue->array[j].ctr;
	return cmp;
}