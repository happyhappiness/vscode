static int init_sizeof_ioinfo(void)
{
	int istty, wastty;
	/* don't init twice */
	if (sizeof_ioinfo)
		return sizeof_ioinfo >= 256;

	sizeof_ioinfo = sizeof(ioinfo);
	wastty = isatty(1);
	while (sizeof_ioinfo < 256) {
		/* toggle FDEV flag, check isatty, then toggle back */
		_pioinfo(1)->osflags ^= FDEV;
		istty = isatty(1);
		_pioinfo(1)->osflags ^= FDEV;
		/* return if we found the correct size */
		if (istty != wastty)
			return 0;
		sizeof_ioinfo += sizeof(void*);
	}
	error("Tweaking file descriptors doesn't work with this MSVCRT.dll");
	return 1;
}