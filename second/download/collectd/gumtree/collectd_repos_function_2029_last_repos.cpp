static int ntpd_get_name_refclock(char *buffer, size_t buffer_size,
                                  struct info_peer_summary const *peer_info) {
  uint32_t refclock_id = ntpd_get_refclock_id(peer_info);
  uint32_t unit_id = ntohl(peer_info->srcadr) & 0x00FF;

  if (((size_t)refclock_id) >= refclock_names_num)
    return ntpd_get_name_from_address(buffer, buffer_size, peer_info, 0);

  if (include_unit_id)
    snprintf(buffer, buffer_size, "%s-%" PRIu32, refclock_names[refclock_id],
             unit_id);
  else
    sstrncpy(buffer, refclock_names[refclock_id], buffer_size);

  return 0;
}