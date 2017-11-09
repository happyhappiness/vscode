static void event_cb(GlobalInfo *g, curl_socket_t s,
                     int action, const boost::system::error_code & error,
                     int *fdp)
{
  fprintf(MSG_OUT, "\nevent_cb: action=%d", action);

  if(socket_map.find(s) == socket_map.end()) {
    fprintf(MSG_OUT, "\nevent_cb: socket already closed");
    return;
  }

  /* make sure the event matches what are wanted */
  if(*fdp == action || *fdp == CURL_POLL_INOUT) {
    CURLMcode rc;
    if(error)
      action = CURL_CSELECT_ERR;
    rc = curl_multi_socket_action(g->multi, s, action, &g->still_running);

    mcode_or_die("event_cb: curl_multi_socket_action", rc);
    check_multi_info(g);

    if(g->still_running <= 0) {
      fprintf(MSG_OUT, "\nlast transfer done, kill timeout");
      timer.cancel();
    }

    /* keep on watching.
     * the socket may have been closed and/or fdp may have been changed
     * in curl_multi_socket_action(), so check them both */
    if(!error && socket_map.find(s) != socket_map.end() &&
       (*fdp == action || *fdp == CURL_POLL_INOUT)) {
      boost::asio::ip::tcp::socket *tcp_socket = socket_map.find(s)->second;

      if(action == CURL_POLL_IN) {
        tcp_socket->async_read_some(boost::asio::null_buffers(),
                                    boost::bind(&event_cb, g, s,
                                                action, _1, fdp));
      }
      if(action == CURL_POLL_OUT) {
        tcp_socket->async_write_some(boost::asio::null_buffers(),
                                     boost::bind(&event_cb, g, s,
                                                 action, _1, fdp));
      }
    }
  }
}