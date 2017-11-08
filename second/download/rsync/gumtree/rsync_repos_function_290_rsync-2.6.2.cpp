void *do_mmap(void *start, int len, int prot, int flags, int fd, OFF_T offset)
{
#if HAVE_OFF64_T
	return mmap64(start, len, prot, flags, fd, offset);
#else
	return mmap(start, len, prot, flags, fd, offset);
#endif
}