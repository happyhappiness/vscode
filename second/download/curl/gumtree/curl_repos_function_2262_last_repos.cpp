static int events_timer(struct Curl_multi *multi,    /* multi handle */
                        long timeout_ms, /* see above */
                        void *userp)    /* private callback pointer */
{
  struct events *ev = userp;
  (void)multi;
  if(timeout_ms == -1)
    /* timeout removed */
    timeout_ms = 0;
  else if(timeout_ms == 0)
    /* timeout is already reached! */
    timeout_ms = 1; /* trigger asap */

  ev->ms = timeout_ms;
  ev->msbump = TRUE;
  return 0;
}