void prio_queue_put(struct prio_queue *queue, void *thing)
{
	prio_queue_compare_fn compare = queue->compare;
	int ix, parent;

	/* Append at the end */
	ALLOC_GROW(queue->array, queue->nr + 1, queue->alloc);
	queue->array[queue->nr++] = thing;
	if (!compare)
		return; /* LIFO */

	/* Bubble up the new one */
	for (ix = queue->nr - 1; ix; ix = parent) {
		parent = (ix - 1) / 2;
		if (compare(queue->array[parent], queue->array[ix],
			    queue->cb_data) <= 0)
			break;

		thing = queue->array[parent];
		queue->array[parent] = queue->array[ix];
		queue->array[ix] = thing;
	}
}