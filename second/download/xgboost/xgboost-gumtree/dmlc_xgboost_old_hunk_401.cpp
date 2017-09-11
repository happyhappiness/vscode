#else
	  close(sockfd);
#endif
	  sockfd = INVALID_SOCKET;
    } else {
      Error("TCPSocket::Close double close the socket or close without create");
    }
