struct timeval tvnow(void)
{
  /*
  ** GetTickCount() is available on _all_ Windows versions from W95 up
  ** to nowadays. Returns milliseconds elapsed since last system boot,
  ** increases monotonically and wraps once 49.7 days have elapsed.
  **
  ** GetTickCount64() is available on Windows version from Windows Vista
  ** and Windows Server 2008 up to nowadays. The resolution of the
  ** function is limited to the resolution of the system timer, which
  ** is typically in the range of 10 milliseconds to 16 milliseconds.
  */
  struct timeval now;
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0600)
  ULONGLONG milliseconds = GetTickCount64();
#else
  DWORD milliseconds = GetTickCount();
#endif
  now.tv_sec = (long)(milliseconds / 1000);
  now.tv_usec = (milliseconds % 1000) * 1000;
  return now;
}