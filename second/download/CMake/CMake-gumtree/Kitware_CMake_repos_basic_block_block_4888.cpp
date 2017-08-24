{
        /* in this case 'entry' is always non-NULL */
        if(multi->socket_cb)
          multi->socket_cb(data,
                           s,
                           CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);
        sh_delentry(&multi->sockhash, s);
      }