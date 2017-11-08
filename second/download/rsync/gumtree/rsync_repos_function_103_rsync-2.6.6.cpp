void read_sum_head(int f, struct sum_struct *sum)
{
	sum->count = read_int(f);
	sum->blength = read_int(f);
	if (sum->blength < 0 || sum->blength > MAX_BLOCK_SIZE) {
		rprintf(FERROR, "Invalid block length %ld [%s]\n",
			(long)sum->blength, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
	sum->s2length = protocol_version < 27 ? csum_length : (int)read_int(f);
	if (sum->s2length < 0 || sum->s2length > MD4_SUM_LENGTH) {
		rprintf(FERROR, "Invalid checksum length %d [%s]\n",
			sum->s2length, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
	sum->remainder = read_int(f);
	if (sum->remainder < 0 || sum->remainder > sum->blength) {
		rprintf(FERROR, "Invalid remainder length %ld [%s]\n",
			(long)sum->remainder, who_am_i());
		exit_cleanup(RERR_PROTOCOL);
	}
}