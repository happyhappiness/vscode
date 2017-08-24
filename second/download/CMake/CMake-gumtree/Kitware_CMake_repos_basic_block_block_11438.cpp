{
		/* little-endian binary cpio archives */
		cpio->read_header = header_bin_le;
		bid += 16;
		/* Is more verification possible here? */
	}