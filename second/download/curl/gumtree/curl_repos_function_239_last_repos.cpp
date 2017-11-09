static int close_socket(void *clientp, curl_socket_t item)
{
  fprintf(MSG_OUT, "\nclose_socket : %d", item);

  std::map<curl_socket_t, boost::asio::ip::tcp::socket *>::iterator it =
    socket_map.find(item);

  if(it != socket_map.end()) {
    delete it->second;
    socket_map.erase(it);
  }

  return 0;
}