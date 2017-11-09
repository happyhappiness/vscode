static void setsock(int *fdp, curl_socket_t s, CURL *e, int act, int oldact,
                    GlobalInfo *g)
{
  fprintf(MSG_OUT, "\nsetsock: socket=%d, act=%d, fdp=%p", s, act, fdp);

  std::map<curl_socket_t, boost::asio::ip::tcp::socket *>::iterator it =
    socket_map.find(s);

  if(it == socket_map.end()) {
    fprintf(MSG_OUT, "\nsocket %d is a c-ares socket, ignoring", s);
    return;
  }

  boost::asio::ip::tcp::socket * tcp_socket = it->second;

  *fdp = act;

  if(act == CURL_POLL_IN) {
    fprintf(MSG_OUT, "\nwatching for socket to become readable");
    if(oldact != CURL_POLL_IN && oldact != CURL_POLL_INOUT) {
      tcp_socket->async_read_some(boost::asio::null_buffers(),
                                  boost::bind(&event_cb, g, s,
                                              CURL_POLL_IN, _1, fdp));
    }
  }
  else if(act == CURL_POLL_OUT) {
    fprintf(MSG_OUT, "\nwatching for socket to become writable");
    if(oldact != CURL_POLL_OUT && oldact != CURL_POLL_INOUT) {
      tcp_socket->async_write_some(boost::asio::null_buffers(),
                                   boost::bind(&event_cb, g, s,
                                               CURL_POLL_OUT, _1, fdp));
    }
  }
  else if(act == CURL_POLL_INOUT) {
    fprintf(MSG_OUT, "\nwatching for socket to become readable & writable");
    if(oldact != CURL_POLL_IN && oldact != CURL_POLL_INOUT) {
      tcp_socket->async_read_some(boost::asio::null_buffers(),
                                  boost::bind(&event_cb, g, s,
                                              CURL_POLL_IN, _1, fdp));
    }
    if(oldact != CURL_POLL_OUT && oldact != CURL_POLL_INOUT) {
      tcp_socket->async_write_some(boost::asio::null_buffers(),
                                   boost::bind(&event_cb, g, s,
                                               CURL_POLL_OUT, _1, fdp));
    }
  }
}