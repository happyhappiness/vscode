void Curl_sndbufset(curl_socket_t sockfd)
{
  int val = CURL_MAX_WRITE_SIZE + 32;
  int curval = 0;
  int curlen = sizeof(curval);
  DWORD majorVersion = 6;

  static int detectOsState = DETECT_OS_NONE;

  if(detectOsState == DETECT_OS_NONE) {
#if !defined(_WIN32_WINNT) || !defined(_WIN32_WINNT_WIN2K) || \
    (_WIN32_WINNT < _WIN32_WINNT_WIN2K)
    OSVERSIONINFO osver;

    memset(&osver, 0, sizeof(osver));
    osver.dwOSVersionInfoSize = sizeof(osver);

    detectOsState = DETECT_OS_PREVISTA;
    if(GetVersionEx(&osver)) {
      if(osver.dwMajorVersion >= majorVersion)
        detectOsState = DETECT_OS_VISTA_OR_LATER;
    }
#else
    ULONGLONG majorVersionMask;
    OSVERSIONINFOEX osver;

    memset(&osver, 0, sizeof(osver));
    osver.dwOSVersionInfoSize = sizeof(osver);
    osver.dwMajorVersion = majorVersion;
    majorVersionMask = VerSetConditionMask(0, VER_MAJORVERSION,
                                           VER_GREATER_EQUAL);

    if(VerifyVersionInfo(&osver, VER_MAJORVERSION, majorVersionMask))
      detectOsState = DETECT_OS_VISTA_OR_LATER;
    else
      detectOsState = DETECT_OS_PREVISTA;
#endif
  }

  if(detectOsState == DETECT_OS_VISTA_OR_LATER)
    return;

  if(getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *)&curval, &curlen) == 0)
    if(curval > val)
      return;

  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const char *)&val, sizeof(val));
}