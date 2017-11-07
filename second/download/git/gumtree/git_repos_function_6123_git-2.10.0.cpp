static inline ioinfo* _pioinfo(int fd)
{
	return (ioinfo*)((char*)__pioinfo[fd >> IOINFO_L2E] +
			(fd & (IOINFO_ARRAY_ELTS - 1)) * sizeof_ioinfo);
}