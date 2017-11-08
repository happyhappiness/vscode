void read_sum_head(int f, struct sum_struct *sum)
{
	sum->count = read_int(f);
	sum->blength = read_int(f);
	if (protocol_version < 27) {
		sum->s2length = csum_length;
	} else {
		sum->s2length = read_int(f);
		if (sum->s2length > MD4_SUM_LENGTH) {
			rprintf(FERROR, "Invalid checksum length %ld\n",
			    (long)sum->s2length);
			exit_cleanup(RERR_PROTOCOL);
		}
	}
	sum->remainder = read_int(f);
}