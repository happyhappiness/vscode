  }
  /*! \brief close the connection */
  inline void Close(void) {
    close(sockfd);
  }
  /*!
   * \brief send data using the socket 
