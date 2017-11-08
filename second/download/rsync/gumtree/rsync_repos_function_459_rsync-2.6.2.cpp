int sys_gettimeofday(struct timeval *tv)
{
#if HAVE_GETTIMEOFDAY_TZ
	return gettimeofday(tv, NULL);
#else
	return gettimeofday(tv);
#endif
}