static void setsock(int *fdp, curl_socket_t s, CURL*e, int act, GlobalInfo*g)
{
  fprintf(MSG_OUT, "\nsetsock: socket=%d, act=%d, fdp=%p", s, act, fdp);

  std::map<curl_socket_t, boost::asio::ip::tcp::socket *>::iterator it = socket_map.find(s);

  if(it == socket_map.end())
  {
    fprintf(MSG_OUT, "\nsocket %d is a c-ares socket, ignoring", s);

    return;
  }

  boost::asio::ip::tcp::socket * tcp_socket = it->second;

  *fdp = act;

  if(act == CURL_POLL_IN)
  {
    fprintf(MSG_OUT, "\nwatching for socket to become readable");

    tcp_socket->async_read_some(boost::asio::null_buffers(),
                                boost::bind(&event_cb, g, tcp_socket, act));
  }
  else if (act == CURL_POLL_OUT)
  {
    fprintf(MSG_OUT, "\nwatching for socket to become writable");

    tcp_socket->async_write_some(boost::asio::null_buffers(),
                                 boost::bind(&event_cb, g, tcp_socket, act));
  }
  else if(act == CURL_POLL_INOUT)
  {
    fprintf(MSG_OUT, "\nwatching for socket to become readable & writable");

    tcp_socket->async_read_some(boost::asio::null_buffers(),
                                boost::bind(&event_cb, g, tcp_socket, act));

    tcp_socket->async_write_some(boost::asio::null_buffers(),
                                 boost::bind(&event_cb, g, tcp_socket, act));
  }
}