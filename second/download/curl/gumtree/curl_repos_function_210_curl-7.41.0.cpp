static void event_cb(GlobalInfo *g, boost::asio::ip::tcp::socket *tcp_socket,
                     int action)
{
  fprintf(MSG_OUT, "\nevent_cb: action=%d", action);

  CURLMcode rc;
  rc = curl_multi_socket_action(g->multi, tcp_socket->native_handle(), action,
                                &g->still_running);

  mcode_or_die("event_cb: curl_multi_socket_action", rc);
  check_multi_info(g);

  if(g->still_running <= 0)
  {
    fprintf(MSG_OUT, "\nlast transfer done, kill timeout");
    timer.cancel();
  }
}