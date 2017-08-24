{
		/*
		 * Compute a POSIX 1003.2 checksum
		 */
		const unsigned char *p;
		size_t nn;

		for (nn = n, p = buff; nn--; ++p)
			COMPUTE_CRC(mtree->crc, *p);
		mtree->crc_len += n;
	}