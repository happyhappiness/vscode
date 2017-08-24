{
		case RC_BIT_0: {
			probability prob = *rc->probs[rc->pos];
			rc->range = (rc->range >> RC_BIT_MODEL_TOTAL_BITS)
					* prob;
			prob += (RC_BIT_MODEL_TOTAL - prob) >> RC_MOVE_BITS;
			*rc->probs[rc->pos] = prob;
			break;
		}

		case RC_BIT_1: {
			probability prob = *rc->probs[rc->pos];
			const uint32_t bound = prob * (rc->range
					>> RC_BIT_MODEL_TOTAL_BITS);
			rc->low += bound;
			rc->range -= bound;
			prob -= prob >> RC_MOVE_BITS;
			*rc->probs[rc->pos] = prob;
			break;
		}

		case RC_DIRECT_0:
			rc->range >>= 1;
			break;

		case RC_DIRECT_1:
			rc->range >>= 1;
			rc->low += rc->range;
			break;

		case RC_FLUSH:
			// Prevent further normalizations.
			rc->range = UINT32_MAX;

			// Flush the last five bytes (see rc_flush()).
			do {
				if (rc_shift_low(rc, out, out_pos, out_size))
					return true;
			} while (++rc->pos < rc->count);

			// Reset the range encoder so we are ready to continue
			// encoding if we weren't finishing the stream.
			rc_reset(rc);
			return false;

		default:
			assert(0);
			break;
		}