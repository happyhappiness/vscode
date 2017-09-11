      ssize_t ret = recv(sockfd, buf,
                         static_cast<sock_size_t>(len - ndone), MSG_WAITALL);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        Socket::Error("RecvAll");
      }
      if (ret == 0) return ndone;
