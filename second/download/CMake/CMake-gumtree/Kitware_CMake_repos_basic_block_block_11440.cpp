(p[0] * 256 + p[1] == 070707) {
		/* big-endian binary cpio archives */
		cpio->read_header = header_bin_be;
		bid += 16;
		/* Is more verification possible here? */
	}