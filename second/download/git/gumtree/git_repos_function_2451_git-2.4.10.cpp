static void range_set_difference(struct range_set *out,
				  struct range_set *a, struct range_set *b)
{
	int i, j =  0;
	for (i = 0; i < a->nr; i++) {
		long start = a->ranges[i].start;
		long end = a->ranges[i].end;
		while (start < end) {
			while (j < b->nr && start >= b->ranges[j].end)
				/*
				 * a:         |-------
				 * b: ------|
				 */
				j++;
			if (j >= b->nr || end < b->ranges[j].start) {
				/*
				 * b exhausted, or
				 * a:  ----|
				 * b:         |----
				 */
				range_set_append(out, start, end);
				break;
			}
			if (start >= b->ranges[j].start) {
				/*
				 * a:     |--????
				 * b: |------|
				 */
				start = b->ranges[j].end;
			} else if (end > b->ranges[j].start) {
				/*
				 * a: |-----|
				 * b:    |--?????
				 */
				if (start < b->ranges[j].start)
					range_set_append(out, start, b->ranges[j].start);
				start = b->ranges[j].end;
			}
		}
	}
}