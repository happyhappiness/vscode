const char *Curl_strerror(struct connectdata *conn, int err)
{
  char *buf, *p;
  size_t max;
  int old_errno = ERRNO;

  DEBUGASSERT(conn);
  DEBUGASSERT(err >= 0);

  buf = conn->syserr_buf;
  max = sizeof(conn->syserr_buf)-1;
  *buf = '\0';

#ifdef USE_WINSOCK

#ifdef _WIN32_WCE
  {
    wchar_t wbuf[256];
    wbuf[0] = L'\0';

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                  LANG_NEUTRAL, wbuf, sizeof(wbuf)/sizeof(wchar_t), NULL);
    wcstombs(buf, wbuf, max);
  }
#else
  /* 'sys_nerr' is the maximum errno number, it is not widely portable */
  if(err >= 0 && err < sys_nerr)
    strncpy(buf, strerror(err), max);
  else {
    if(!get_winsock_error(err, buf, max) &&
       !FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                       LANG_NEUTRAL, buf, (DWORD)max, NULL))
      snprintf(buf, max, "Unknown error %d (%#x)", err, err);
  }
#endif

#else /* not USE_WINSOCK coming up */

#if defined(HAVE_STRERROR_R) && defined(HAVE_POSIX_STRERROR_R)
 /*
  * The POSIX-style strerror_r() may set errno to ERANGE if insufficient
  * storage is supplied via 'strerrbuf' and 'buflen' to hold the generated
  * message string, or EINVAL if 'errnum' is not a valid error number.
  */
  if(0 != strerror_r(err, buf, max)) {
    if('\0' == buf[0])
      snprintf(buf, max, "Unknown error %d", err);
  }
#elif defined(HAVE_STRERROR_R) && defined(HAVE_GLIBC_STRERROR_R)
 /*
  * The glibc-style strerror_r() only *might* use the buffer we pass to
  * the function, but it always returns the error message as a pointer,
  * so we must copy that string unconditionally (if non-NULL).
  */
  {
    char buffer[256];
    char *msg = strerror_r(err, buffer, sizeof(buffer));
    if(msg)
      strncpy(buf, msg, max);
    else
      snprintf(buf, max, "Unknown error %d", err);
  }
#elif defined(HAVE_STRERROR_R) && defined(HAVE_VXWORKS_STRERROR_R)
 /*
  * The vxworks-style strerror_r() does use the buffer we pass to the function.
  * The buffer size should be at least NAME_MAX (256)
  */
  {
    char buffer[256];
    if(OK == strerror_r(err, buffer))
      strncpy(buf, buffer, max);
    else
      snprintf(buf, max, "Unknown error %d", err);
  }
#else
  {
    char *msg = strerror(err);
    if(msg)
      strncpy(buf, msg, max);
    else
      snprintf(buf, max, "Unknown error %d", err);
  }
#endif

#endif /* end of ! USE_WINSOCK */

  buf[max] = '\0'; /* make sure the string is zero terminated */

  /* strip trailing '\r\n' or '\n'. */
  p = strrchr(buf, '\n');
  if(p && (p - buf) >= 2)
    *p = '\0';
  p = strrchr(buf, '\r');
  if(p && (p - buf) >= 1)
    *p = '\0';

  if(old_errno != ERRNO)
    SET_ERRNO(old_errno);

  return buf;
}