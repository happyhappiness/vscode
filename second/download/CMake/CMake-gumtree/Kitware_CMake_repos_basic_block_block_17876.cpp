(r & 1)
					r = (r >> 1) ^ poly64;
				else
					r >>= 1