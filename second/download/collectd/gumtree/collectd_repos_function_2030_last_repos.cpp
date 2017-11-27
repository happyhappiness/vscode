static int ntpd_get_name(char *buffer, size_t buffer_size,
                         struct info_peer_summary const *peer_info) {
  uint32_t addr = ntohl(peer_info->srcadr);

  if (!peer_info->v6_flag && ((addr & REFCLOCK_MASK) == REFCLOCK_ADDR))
    return ntpd_get_name_refclock(buffer, buffer_size, peer_info);
  else
    return ntpd_get_name_from_address(buffer, buffer_size, peer_info,
                                      do_reverse_lookups);
}