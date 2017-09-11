  /*! \brief the file descriptor of socket */
  int sockfd;
  // constructor
  TCPSocket(void) : sockfd(-1) {
  }
  explicit TCPSocket(int sockfd) : sockfd(sockfd) {
  }
  ~TCPSocket(void) {
    if (sockfd != -1) this->Close();
  }
  // default conversion to int
  inline operator int() const {
    return sockfd;
  }
  /*!
   * \brief create the socket, call this before using socket
   * \param af domain
   */
  inline void Create(int af = PF_INET) {
    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
      SockError("Create", errno);
    }
  }
  /*!
   * \brief start up the socket module
   *   call this before using the sockets
   */
