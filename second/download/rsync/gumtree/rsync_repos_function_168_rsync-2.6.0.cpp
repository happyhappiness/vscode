static void sum_sizes_sqroot(struct sum_struct *sum, uint64 len)
{
	extern int block_size;
	int blength, s2length, b;
	uint32 c;
	uint64 l;

	if (block_size) {
		blength = block_size;
	} else if (len <= BLOCK_SIZE * BLOCK_SIZE) {
		blength = BLOCK_SIZE;
	} else {
		l = len;
		c = 1;
		while (l >>= 2) {
			c <<= 1;
		}
		blength = 0;
		do {
			blength |= c;
			if (len < (uint64)blength * blength)
				blength &= ~c;
			c >>= 1;
		} while (c >= 8);	/* round to multiple of 8 */
		blength = MAX(blength, BLOCK_SIZE);
	}

	if (protocol_version < 27) {
		s2length = csum_length;
	} else if (csum_length == SUM_LENGTH) {
		s2length = SUM_LENGTH;
	} else {
		b = BLOCKSUM_BIAS;
		l = len;
		while (l >>= 1) {
			b += 2;
		}
		c = blength;
		while (c >>= 1 && b) {
			b--;
		}
		s2length = (b + 1 - 32 + 7) / 8; /* add a bit,
						  * subtract rollsum,
						  * round up
						  *    --optimize in compiler--
						  */
		s2length = MAX(s2length, csum_length);
		s2length = MIN(s2length, SUM_LENGTH);
	}

	sum->flength	= len;
	sum->blength	= blength;
	sum->s2length	= s2length;
	sum->count	= (len + (blength - 1)) / blength;
	sum->remainder	= (len % blength);

	if (sum->count && verbose > 2) {
		rprintf(FINFO, "count=%ld rem=%ld blength=%ld s2length=%ld flength=%.0f\n",
			(long) sum->count, (long) sum->remainder,
			(long) sum->blength, (long) sum->s2length,
			(double) sum->flength);
	}
}