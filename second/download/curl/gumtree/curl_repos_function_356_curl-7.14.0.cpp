const char *Curl_strerror(struct connectdata *conn, int err)
{
  char *buf, *p;
  size_t max;

  curlassert(conn);
  curlassert(err >= 0);

  buf = conn->syserr_buf;
  max = sizeof(conn->syserr_buf)-1;
  *buf = '\0';

#if defined(WIN32) && !defined(__CYGWIN__)

#ifdef _WIN32_WCE
  buf[0]=0;
  {
    wchar_t wbuf[256];

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                  LANG_NEUTRAL, wbuf, sizeof(wbuf)/sizeof(wchar_t), NULL);
    wcstombs(buf,wbuf,max);
  }

#else

  /* 'sys_nerr' is the maximum errno number, it is not widely portable */
  if (err >= 0 && err < sys_nerr)
    strncpy(buf, strerror(err), max);
  else {
    if (!get_winsock_error(err, buf, max) &&
        !FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err,
                       LANG_NEUTRAL, buf, (DWORD)max, NULL))
      snprintf(buf, max, "Unknown error %d (%#x)", err, err);
  }
#endif
#else /* not native Windows coming up */

  /* These should be atomic and hopefully thread-safe */
#ifdef HAVE_STRERROR_R
  /* There are two different APIs for strerror_r(). The POSIX and the GLIBC
     versions. */
#ifdef HAVE_POSIX_STRERROR_R
  strerror_r(err, buf, max);
  /* this may set errno to ERANGE if insufficient storage was supplied via
     'strerrbuf' and 'buflen' to contain the generated message string, or
     EINVAL if the value of 'errnum' is not a valid error number.*/
#else
  {
    /* HAVE_GLIBC_STRERROR_R */
    char buffer[256];
    char *msg = strerror_r(err, buffer, sizeof(buffer));
    /* this version of strerror_r() only *might* use the buffer we pass to
       the function, but it always returns the error message as a pointer,
       so we must copy that string unconditionally */
    strncpy(buf, msg, max);
  }
#endif /* end of HAVE_GLIBC_STRERROR_R */
#else /* HAVE_STRERROR_R */
  strncpy(buf, strerror(err), max);
#endif /* end of HAVE_STRERROR_R */
#endif /* end of ! Windows */

  buf[max] = '\0'; /* make sure the string is zero terminated */

  /* strip trailing '\r\n' or '\n'. */
  if ((p = strrchr(buf,'\n')) != NULL && (p - buf) >= 2)
     *p = '\0';
  if ((p = strrchr(buf,'\r')) != NULL && (p - buf) >= 1)
     *p = '\0';
  return buf;
}