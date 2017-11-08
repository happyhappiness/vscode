int Curl_ourerrno(void)
{
#ifdef WIN32
  return (int)GetLastError();
#else
  return errno;
#endif
}