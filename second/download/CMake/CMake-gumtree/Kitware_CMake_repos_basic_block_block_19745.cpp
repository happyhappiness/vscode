(ioctl(sockfd, SIOCGARP, (char*)&arpreq) == -1) {
    uv__close(sockfd);
    return -errno;
  }