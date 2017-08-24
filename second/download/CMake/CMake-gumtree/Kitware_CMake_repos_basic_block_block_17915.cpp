{
	// For now, if the data doesn't compress, we always use uncompressed
	// chunks of LZMA2. In future we may use Subblock filter too, but
	// but for simplicity we probably will still use the same bound
	// calculation even though Subblock filter would have slightly less
	// overhead.
	lzma_vli lzma2_size = lzma2_bound(uncompressed_size);
	if (lzma2_size == 0)
		return 0;

	// Take Block Padding into account.
	lzma2_size = (lzma2_size + 3) & ~LZMA_VLI_C(3);

#if SIZE_MAX < LZMA_VLI_MAX
	// Catch the possible integer overflow on 32-bit systems. There's no
	// overflow on 64-bit systems, because lzma2_bound() already takes
	// into account the size of the headers in the Block.
	if (SIZE_MAX - HEADERS_BOUND < lzma2_size)
		return 0;
#endif

	return HEADERS_BOUND + lzma2_size;
}