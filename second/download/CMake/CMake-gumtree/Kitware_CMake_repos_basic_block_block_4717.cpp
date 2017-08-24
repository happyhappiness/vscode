{
    struct Curl_message *msg = e->ptr;

    if(msg->extmsg.easy_handle == easy) {
      Curl_llist_remove(&multi->msglist, e, NULL);
      /* there can only be one from this specific handle */
      break;
    }
  }