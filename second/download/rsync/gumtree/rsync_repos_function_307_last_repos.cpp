static void sum_sizes_sqroot(struct sum_struct *sum, int64 len)
{
	int32 blength;
	int s2length;
	int64 l;

	if (len < 0) {
		/* The file length overflowed our int64 var, so we can't process this file. */
		sum->count = -1; /* indicate overflow error */
		return;
	}

	if (block_size)
		blength = block_size;
	else if (len <= BLOCK_SIZE * BLOCK_SIZE)
		blength = BLOCK_SIZE;
	else {
		int32 max_blength = protocol_version < 30 ? OLD_MAX_BLOCK_SIZE : MAX_BLOCK_SIZE;
		int32 c;
		int cnt;
		for (c = 1, l = len, cnt = 0; l >>= 2; c <<= 1, cnt++) {}
		if (c < 0 || c >= max_blength)
			blength = max_blength;
		else {
		    blength = 0;
		    do {
			    blength |= c;
			    if (len < (int64)blength * blength)
				    blength &= ~c;
			    c >>= 1;
		    } while (c >= 8);	/* round to multiple of 8 */
		    blength = MAX(blength, BLOCK_SIZE);
		}
	}

	if (protocol_version < 27) {
		s2length = csum_length;
	} else if (csum_length == SUM_LENGTH) {
		s2length = SUM_LENGTH;
	} else {
		int32 c;
		int b = BLOCKSUM_BIAS;
		for (l = len; l >>= 1; b += 2) {}
		for (c = blength; (c >>= 1) && b; b--) {}
		/* add a bit, subtract rollsum, round up. */
		s2length = (b + 1 - 32 + 7) / 8; /* --optimize in compiler-- */
		s2length = MAX(s2length, csum_length);
		s2length = MIN(s2length, SUM_LENGTH);
	}

	sum->flength	= len;
	sum->blength	= blength;
	sum->s2length	= s2length;
	sum->remainder	= (int32)(len % blength);
	sum->count	= (int32)(l = (len / blength) + (sum->remainder != 0));

	if ((int64)sum->count != l)
		sum->count = -1;

	if (sum->count && DEBUG_GTE(DELTASUM, 2)) {
		rprintf(FINFO,
			"count=%s rem=%ld blength=%ld s2length=%d flength=%s\n",
			big_num(sum->count), (long)sum->remainder, (long)sum->blength,
			sum->s2length, big_num(sum->flength));
	}
}