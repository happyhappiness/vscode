(r & 1)
					r = (r >> 1) ^ poly32;
				else
					r >>= 1