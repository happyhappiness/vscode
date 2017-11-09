void *prio_queue_get(struct prio_queue *queue)
{
	void *result;
	int ix, child;

	if (!queue->nr)
		return NULL;
	if (!queue->compare)
		return queue->array[--queue->nr].data; /* LIFO */

	result = queue->array[0].data;
	if (!--queue->nr)
		return result;

	queue->array[0] = queue->array[queue->nr];

	/* Push down the one at the root */
	for (ix = 0; ix * 2 + 1 < queue->nr; ix = child) {
		child = ix * 2 + 1; /* left */
		if (child + 1 < queue->nr &&
		    compare(queue, child, child + 1) >= 0)
			child++; /* use right child */

		if (compare(queue, ix, child) <= 0)
			break;

		swap(queue, child, ix);
	}
	return result;
}