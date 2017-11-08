void Curl_multi_process_pending_handles(struct Curl_multi *multi)
{
  struct SessionHandle *data;

  data=multi->easyp;
  while(data) {
    if(data->mstate == CURLM_STATE_CONNECT_PEND) {
      multistate(data, CURLM_STATE_CONNECT);
      /* Make sure that the handle will be processed soonish. */
      Curl_expire(data, 1);
    }
    data = data->next; /* operate on next handle */
  }
}