{
		int j, last = i;

		t->sparse_list[i].offset = aligned;
		t->sparse_list[i].length = 0;
		for (i = 0; i < last; i++) {
			if ((t->sparse_list[i].offset +
			       t->sparse_list[i].length) <= 
					t->sparse_list[i+1].offset)
				continue;
			/*
			 * Now sparse_list[i+1] is overlapped by sparse_list[i].
			 * Merge those two.
			 */
			length = t->sparse_list[i+1].offset -
					t->sparse_list[i].offset;
			t->sparse_list[i+1].offset = t->sparse_list[i].offset;
			t->sparse_list[i+1].length += length;
			/* Remove sparse_list[i]. */
			for (j = i; j < last; j++) {
				t->sparse_list[j].offset =
				    t->sparse_list[j+1].offset;
				t->sparse_list[j].length =
				    t->sparse_list[j+1].length;
			}
			last--;
		}
	}