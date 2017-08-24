(ioctl(sockfd, SIOCGSIZIFCONF, &size) == -1) {
    uv__close(sockfd);
    return -errno;
  }