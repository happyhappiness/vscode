{
			case 0: /* Use repeated offset 0. */
				copy_pos = r0;
				state = ST_REAL_POS;
				continue;
			case 1: /* Use repeated offset 1. */
				copy_pos = r1;
				/* Swap repeated offset. */
				r1 = r0;
				r0 = copy_pos;
				state = ST_REAL_POS;
				continue;
			case 2: /* Use repeated offset 2. */
				copy_pos = r2;
				/* Swap repeated offset. */
				r2 = r0;
				r0 = copy_pos;
				state = ST_REAL_POS;
				continue;
			default:
				offset_bits =
				    pos_tbl[position_slot].footer_bits;
				break;
			}