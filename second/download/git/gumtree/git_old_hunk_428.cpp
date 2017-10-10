	offset += bytes;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(consumed_bytes, bytes))
		die("pack too large for current definition of off_t");
	consumed_bytes += bytes;
}

static void *get_data(unsigned long size)
{
	git_zstream stream;
	void *buf = xmallocz(size);
