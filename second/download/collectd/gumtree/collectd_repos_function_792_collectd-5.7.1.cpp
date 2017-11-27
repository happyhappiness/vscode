static int handle_udp(const struct udphdr *udp, int len) {
  char buf[PCAP_SNAPLEN];
  if ((ntohs(udp->UDP_DEST) != 53) && (ntohs(udp->UDP_SRC) != 53))
    return 0;
  memcpy(buf, udp + 1, len - sizeof(*udp));
  if (0 == handle_dns(buf, len - sizeof(*udp)))
    return 0;
  return 1;
}