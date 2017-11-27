static int handle_linux_sll(const u_char *pkt, int len) {
  struct sll_header {
    uint16_t pkt_type;
    uint16_t dev_type;
    uint16_t addr_len;
    uint8_t addr[8];
    uint16_t proto_type;
  } * hdr;
  uint16_t etype;

  if ((0 > len) || ((unsigned int)len < sizeof(struct sll_header)))
    return 0;

  hdr = (struct sll_header *)pkt;
  pkt = (u_char *)(hdr + 1);
  len -= sizeof(struct sll_header);

  etype = ntohs(hdr->proto_type);

  if ((ETHERTYPE_IP != etype) && (ETHERTYPE_IPV6 != etype))
    return 0;

  if (ETHERTYPE_IPV6 == etype)
    return handle_ipv6((void *)pkt, len);
  else
    return handle_ip((struct ip *)pkt, len);
}