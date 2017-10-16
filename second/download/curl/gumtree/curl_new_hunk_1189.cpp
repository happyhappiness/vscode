    /* unknown tag and its companion, just ignore: */
    return CURLE_READ_ERROR; /* correct this */
  }
  return CURLE_OK;
}

#if !defined(WIN32)||defined(__CYGWIN32__)
#ifndef RETSIGTYPE
#define RETSIGTYPE void
#endif
static
RETSIGTYPE alarmfunc(int signal)
{
  /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
  (void)signal;
  return;
}
#endif

CURLcode curl_disconnect(CURLconnect *c_connect)
{
  struct connectdata *conn = c_connect;

  struct UrlData *data = conn->data;

