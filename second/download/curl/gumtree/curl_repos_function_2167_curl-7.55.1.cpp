static CURLcode easy_transfer(struct Curl_multi *multi)
{
  bool done = FALSE;
  CURLMcode mcode = CURLM_OK;
  CURLcode result = CURLE_OK;
  struct curltime before;
  int without_fds = 0;  /* count number of consecutive returns from
                           curl_multi_wait() without any filedescriptors */

  while(!done && !mcode) {
    int still_running = 0;
    int rc;

    before = curlx_tvnow();
    mcode = curl_multi_wait(multi, NULL, 0, 1000, &rc);

    if(!mcode) {
      if(!rc) {
        struct curltime after = curlx_tvnow();

        /* If it returns without any filedescriptor instantly, we need to
           avoid busy-looping during periods where it has nothing particular
           to wait for */
        if(curlx_tvdiff(after, before) <= 10) {
          without_fds++;
          if(without_fds > 2) {
            int sleep_ms = without_fds < 10 ? (1 << (without_fds - 1)) : 1000;
            Curl_wait_ms(sleep_ms);
          }
        }
        else
          /* it wasn't "instant", restart counter */
          without_fds = 0;
      }
      else
        /* got file descriptor, restart counter */
        without_fds = 0;

      mcode = curl_multi_perform(multi, &still_running);
    }

    /* only read 'still_running' if curl_multi_perform() return OK */
    if(!mcode && !still_running) {
      CURLMsg *msg = curl_multi_info_read(multi, &rc);
      if(msg) {
        result = msg->data.result;
        done = TRUE;
      }
    }
  }

  /* Make sure to return some kind of error if there was a multi problem */
  if(mcode) {
    result = (mcode == CURLM_OUT_OF_MEMORY) ? CURLE_OUT_OF_MEMORY :
              /* The other multi errors should never happen, so return
                 something suitably generic */
              CURLE_BAD_FUNCTION_ARGUMENT;
  }

  return result;
}