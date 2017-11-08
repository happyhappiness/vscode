OFF_T do_lseek(int fd, OFF_T offset, int whence)
{
#if HAVE_OFF64_T
	off64_t lseek64();
	return lseek64(fd, offset, whence);
#else
	return lseek(fd, offset, whence);
#endif
}