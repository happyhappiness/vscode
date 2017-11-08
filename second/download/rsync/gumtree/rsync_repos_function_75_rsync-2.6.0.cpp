static void sleep_for_bwlimit(int bytes_written)
{
	struct timeval tv;

	if (!bwlimit)
		return;

	assert(bytes_written > 0);
	assert(bwlimit > 0);

	tv.tv_usec = bytes_written * 1000 / bwlimit;
	tv.tv_sec  = tv.tv_usec / 1000000;
	tv.tv_usec = tv.tv_usec % 1000000;

	select(0, NULL, NULL, NULL, &tv);
}