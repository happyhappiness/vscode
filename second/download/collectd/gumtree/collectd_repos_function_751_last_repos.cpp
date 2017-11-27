static int handle_ether(const u_char *pkt, int len) {
  char buf[PCAP_SNAPLEN];
  struct ether_header *e = (void *)pkt;
  unsigned short etype = ntohs(e->ether_type);
  if (len < ETHER_HDR_LEN)
    return 0;
  pkt += ETHER_HDR_LEN;
  len -= ETHER_HDR_LEN;
  if (ETHERTYPE_8021Q == etype) {
    etype = ntohs(*(unsigned short *)(pkt + 2));
    pkt += 4;
    len -= 4;
  }
  if ((ETHERTYPE_IP != etype) && (ETHERTYPE_IPV6 != etype))
    return 0;
  memcpy(buf, pkt, len);
  if (ETHERTYPE_IPV6 == etype)
    return handle_ipv6((void *)buf, len);
  else
    return handle_ip((struct ip *)buf, len);
}