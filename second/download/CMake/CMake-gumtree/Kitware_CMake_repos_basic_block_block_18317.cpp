do {
				if (rc_shift_low(rc, out, out_pos, out_size))
					return true;
			} while (++rc->pos < rc->count);