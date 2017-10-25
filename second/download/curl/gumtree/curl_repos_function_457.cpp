CURLMsg *curl_multi_info_read(CURLM *multi_handle, int *msgs_in_queue)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;

  *msgs_in_queue = 0; /* default to none */

  if(GOOD_MULTI_HANDLE(multi)) {
    struct Curl_one_easy *easy;

    if(!multi->num_msgs)
      return NULL; /* no messages left to return */

    easy=multi->easy.next;
    while(easy) {
      if(easy->msg_num) {
        easy->msg_num--;
        break;
      }
      easy = easy->next;
    }
    if(!easy)
      return NULL; /* this means internal count confusion really */

    multi->num_msgs--;
    *msgs_in_queue = multi->num_msgs;

    return &easy->msg->extmsg;
  }
  else
    return NULL;
}