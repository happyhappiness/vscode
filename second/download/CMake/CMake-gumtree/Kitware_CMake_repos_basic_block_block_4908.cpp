{
      if(multi->socket_cb)
        multi->socket_cb(conn->data, s, CURL_POLL_REMOVE,
                         multi->socket_userp,
                         entry->socketp);

      /* now remove it from the socket hash */
      sh_delentry(&multi->sockhash, s);
    }