static int net_send(int *sockfd, const char *buff, int len) {
  uint16_t packet_size;

  assert(len > 0);
  assert(*sockfd >= 0);

  /* send short containing size of data packet */
  packet_size = htons((uint16_t)len);

  if (swrite(*sockfd, (void *)&packet_size, sizeof(packet_size)) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return -1;
  }

  /* send data packet */
  if (swrite(*sockfd, (void *)buff, len) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return -2;
  }

  return 0;
}