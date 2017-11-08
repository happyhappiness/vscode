static int multi_timer_cb(CURLM *multi, long timeout_ms, GlobalInfo *g)
{
  fprintf(MSG_OUT, "\nmulti_timer_cb: timeout_ms %ld", timeout_ms);

  /* cancel running timer */
  timer.cancel();

  if(timeout_ms > 0) {
    /* update timer */
    timer.expires_from_now(boost::posix_time::millisec(timeout_ms));
    timer.async_wait(boost::bind(&timer_cb, _1, g));
  }
  else if(timeout_ms == 0) {
    /* call timeout function immediately */
    boost::system::error_code error; /*success*/
    timer_cb(error, g);
  }

  return 0;
}