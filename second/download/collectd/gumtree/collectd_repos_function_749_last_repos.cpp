static int handle_loop(const u_char *pkt, int len) {
  unsigned int family;
  memcpy(&family, pkt, sizeof(family));
  if (AF_INET != ntohl(family))
    return 0;
  return handle_ip((struct ip *)(pkt + 4), len - 4);
}