int do_fallocate(int fd, OFF_T offset, OFF_T length)
{
#ifdef FALLOC_FL_KEEP_SIZE
#define DO_FALLOC_OPTIONS FALLOC_FL_KEEP_SIZE
#else
#define DO_FALLOC_OPTIONS 0
#endif
	RETURN_ERROR_IF(dry_run, 0);
	RETURN_ERROR_IF_RO_OR_LO;
#if defined HAVE_FALLOCATE
	return fallocate(fd, DO_FALLOC_OPTIONS, offset, length);
#elif defined HAVE_SYS_FALLOCATE
	return syscall(SYS_fallocate, fd, DO_FALLOC_OPTIONS, (loff_t)offset, (loff_t)length);
#elif defined HAVE_EFFICIENT_POSIX_FALLOCATE
	return posix_fallocate(fd, offset, length);
#else
#error Coding error in SUPPORT_PREALLOCATION logic.
#endif
}