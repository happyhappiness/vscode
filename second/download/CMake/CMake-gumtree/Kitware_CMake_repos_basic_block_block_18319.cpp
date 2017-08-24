{
			if (rc_shift_low(rc, out, out_pos, out_size))
				return true;

			rc->range <<= RC_SHIFT_BITS;
		}