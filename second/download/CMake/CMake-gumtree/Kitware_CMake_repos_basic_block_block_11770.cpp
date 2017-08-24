{
		b = a + a + 1; /* First child */
		if (b >= heap->cnt)
			return;
		b_offset = heap->reqs[b].offset;
		c = b + 1; /* Use second child if it is smaller. */
		if (c < heap->cnt) {
			c_offset = heap->reqs[c].offset;
			if (c_offset < b_offset) {
				b = c;
				b_offset = c_offset;
			}
		}
		if (a_offset <= b_offset)
			return;
		tmp = heap->reqs[a];
		heap->reqs[a] = heap->reqs[b];
		heap->reqs[b] = tmp;
		a = b;
	}