{
		b = a + a + 1; /* First child */
		if (b >= heap->used)
			return (r);
		b_key = heap->files[b]->key;
		c = b + 1; /* Use second child if it is smaller. */
		if (c < heap->used) {
			c_key = heap->files[c]->key;
			if (c_key < b_key) {
				b = c;
				b_key = c_key;
			}
		}
		if (a_key <= b_key)
			return (r);
		tmp = heap->files[a];
		heap->files[a] = heap->files[b];
		heap->files[b] = tmp;
		a = b;
	}