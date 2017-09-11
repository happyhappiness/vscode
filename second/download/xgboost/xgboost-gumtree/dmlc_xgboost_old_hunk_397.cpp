#else
	  close(sockfd);
#endif
	  sockfd = INVALID_sock_t;
    } else {
      Error("TCPSocket::Close double close the socket or close without create");
    }
