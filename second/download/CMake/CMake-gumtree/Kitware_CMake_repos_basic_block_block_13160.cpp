{
		b = a + a + 1; /* First child */
		if (b >= heap->used)
			return (r);
		b_id = heap->files[b]->id;
		c = b + 1; /* Use second child if it is smaller. */
		if (c < heap->used) {
			c_id = heap->files[c]->id;
			if (c_id < b_id) {
				b = c;
				b_id = c_id;
			}
		}
		if (a_id <= b_id)
			return (r);
		tmp = heap->files[a];
		heap->files[a] = heap->files[b];
		heap->files[b] = tmp;
		a = b;
	}