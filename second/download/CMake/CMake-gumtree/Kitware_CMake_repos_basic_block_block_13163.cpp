(c < heap->used) {
			c_id = heap->files[c]->id;
			if (c_id < b_id) {
				b = c;
				b_id = c_id;
			}
		}