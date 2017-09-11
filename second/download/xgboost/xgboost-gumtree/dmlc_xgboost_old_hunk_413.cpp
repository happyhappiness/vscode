      ssize_t ret = recv(sockfd, buf, len - ndone, MSG_WAITALL);
      if (ret == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) return ndone;
        SockError("Recv", errno);
      }
      if (ret == 0) return ndone;
      buf += ret;
