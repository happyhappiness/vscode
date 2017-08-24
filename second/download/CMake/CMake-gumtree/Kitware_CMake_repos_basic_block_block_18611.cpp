(ioctl(sockfd, SIOCGIFFLAGS, &flg) == -1) {
      uv__close(sockfd);
      return -errno;
    }