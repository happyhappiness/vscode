static CURLMcode multi_addmsg(struct Curl_multi *multi,
                              struct Curl_message *msg)
{
  Curl_llist_insert_next(&multi->msglist, multi->msglist.tail, msg,
                         &msg->list);
  return CURLM_OK;
}