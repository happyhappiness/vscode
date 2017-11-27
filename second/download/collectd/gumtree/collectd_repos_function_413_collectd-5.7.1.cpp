static int net_recv(int *sockfd, char *buf, int buflen) {
  uint16_t packet_size;

  /* get data size -- in short */
  if (sread(*sockfd, (void *)&packet_size, sizeof(packet_size)) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return (-1);
  }

  packet_size = ntohs(packet_size);
  if (packet_size > buflen) {
    ERROR("apcups plugin: Received %" PRIu16 " bytes of payload "
          "but have only %i bytes of buffer available.",
          packet_size, buflen);
    close(*sockfd);
    *sockfd = -1;
    return (-2);
  }

  if (packet_size == 0)
    return (0);

  /* now read the actual data */
  if (sread(*sockfd, (void *)buf, packet_size) != 0) {
    close(*sockfd);
    *sockfd = -1;
    return (-1);
  }

  return ((int)packet_size);
}