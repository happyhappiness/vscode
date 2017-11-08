static void get_posix_time(long *_out, const void *_in)
{
#ifdef HAVE_LONGLONG
  long long timestamp = *(long long *) _in;
#else
  unsigned __int64 timestamp = *(unsigned __int64 *) _in;
#endif

  timestamp -= 116444736000000000ULL;
  timestamp /= 10000000;
  *_out = (long) timestamp;
}