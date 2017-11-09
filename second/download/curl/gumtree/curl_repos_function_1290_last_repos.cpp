struct curltime curlx_tvnow(void)
{
  /*
  ** GetTickCount() is available on _all_ Windows versions from W95 up
  ** to nowadays. Returns milliseconds elapsed since last system boot,
  ** increases monotonically and wraps once 49.7 days have elapsed.
  */
  struct curltime now;
#if !defined(_WIN32_WINNT) || !defined(_WIN32_WINNT_VISTA) || \
    (_WIN32_WINNT < _WIN32_WINNT_VISTA)
  DWORD milliseconds = GetTickCount();
  now.tv_sec = milliseconds / 1000;
  now.tv_usec = (milliseconds % 1000) * 1000;
#else
  ULONGLONG milliseconds = GetTickCount64();
  now.tv_sec = (time_t) (milliseconds / 1000);
  now.tv_usec = (unsigned int) (milliseconds % 1000) * 1000;
#endif

  return now;
}