{
			c_offset = heap->reqs[c].offset;
			if (c_offset < b_offset) {
				b = c;
				b_offset = c_offset;
			}
		}