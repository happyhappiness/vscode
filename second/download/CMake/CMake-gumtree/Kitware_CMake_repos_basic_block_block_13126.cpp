{
	int r;

	/* Init decompress library. */
	if ((r = decompression_init(a, encoding)) != ARCHIVE_OK)
		return (r);
	/* Init checksum library. */
	checksum_init(a, a_sum_alg, e_sum_alg);
	return (ARCHIVE_OK);
}