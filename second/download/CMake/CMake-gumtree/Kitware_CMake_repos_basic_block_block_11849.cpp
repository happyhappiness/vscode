{
			c_key = heap->files[c]->key;
			if (c_key < b_key) {
				b = c;
				b_key = c_key;
			}
		}