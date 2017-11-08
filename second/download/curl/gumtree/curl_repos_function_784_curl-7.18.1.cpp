static int update_timer(struct Curl_multi *multi)
{
  long timeout_ms;
  if(!multi->timer_cb)
    return 0;
  if( multi_timeout(multi, &timeout_ms) != CURLM_OK )
    return -1;
  if( timeout_ms < 0 )
    return 0;

  /* When multi_timeout() is done, multi->timetree points to the node with the
   * timeout we got the (relative) time-out time for. We can thus easily check
   * if this is the same (fixed) time as we got in a previous call and then
   * avoid calling the callback again. */
  if(multi->timetree->key == multi->timer_lastcall)
    return 0;

  multi->timer_lastcall = multi->timetree->key;

  return multi->timer_cb((CURLM*)multi, timeout_ms, multi->timer_userp);
}