static void read_v2_anomalous_offsets(struct packed_git *p,
				      struct pack_idx_option *opts)
{
	const uint32_t *idx1, *idx2;
	uint32_t i;

	/* The address of the 4-byte offset table */
	idx1 = (((const uint32_t *)p->index_data)
		+ 2 /* 8-byte header */
		+ 256 /* fan out */
		+ 5 * p->num_objects /* 20-byte SHA-1 table */
		+ p->num_objects /* CRC32 table */
		);

	/* The address of the 8-byte offset table */
	idx2 = idx1 + p->num_objects;

	for (i = 0; i < p->num_objects; i++) {
		uint32_t off = ntohl(idx1[i]);
		if (!(off & 0x80000000))
			continue;
		off = off & 0x7fffffff;
		if (idx2[off * 2])
			continue;
		/*
		 * The real offset is ntohl(idx2[off * 2]) in high 4
		 * octets, and ntohl(idx2[off * 2 + 1]) in low 4
		 * octets.  But idx2[off * 2] is Zero!!!
		 */
		ALLOC_GROW(opts->anomaly, opts->anomaly_nr + 1, opts->anomaly_alloc);
		opts->anomaly[opts->anomaly_nr++] = ntohl(idx2[off * 2 + 1]);
	}

	if (1 < opts->anomaly_nr)
		qsort(opts->anomaly, opts->anomaly_nr, sizeof(uint32_t), cmp_uint32);
}