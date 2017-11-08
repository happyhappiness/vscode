static curl_socket_t opensocket(void *clientp, curlsocktype purpose,
                                struct curl_sockaddr *address)
{
  fprintf(MSG_OUT, "\nopensocket :");

  curl_socket_t sockfd = CURL_SOCKET_BAD;

  /* restrict to IPv4 */
  if(purpose == CURLSOCKTYPE_IPCXN && address->family == AF_INET)
  {
    /* create a tcp socket object */
    boost::asio::ip::tcp::socket *tcp_socket = new boost::asio::ip::tcp::socket(io_service);

    /* open it and get the native handle*/
    boost::system::error_code ec;
    tcp_socket->open(boost::asio::ip::tcp::v4(), ec);

    if(ec)
    {
      /* An error occurred */
      std::cout << std::endl << "Couldn't open socket [" << ec << "][" << ec.message() << "]";
      fprintf(MSG_OUT, "\nERROR: Returning CURL_SOCKET_BAD to signal error");
    }
    else
    {
      sockfd = tcp_socket->native_handle();
      fprintf(MSG_OUT, "\nOpened socket %d", sockfd);

      /* save it for monitoring */
      socket_map.insert(std::pair<curl_socket_t, boost::asio::ip::tcp::socket *>(sockfd, tcp_socket));
    }
  }

  return sockfd;
}