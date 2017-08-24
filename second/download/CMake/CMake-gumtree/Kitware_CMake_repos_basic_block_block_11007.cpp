{
	const void *h;

	(void)best_bid; /* UNUSED */

	/*
	 * Verify the 8-byte file signature.
	 * TODO: Do we need to check more than this?
	 */
	if ((h = __archive_read_ahead(a, 8, NULL)) == NULL)
		return (-1);
	if (memcmp(h, "!<arch>\n", 8) == 0) {
		return (64);
	}
	return (-1);
}