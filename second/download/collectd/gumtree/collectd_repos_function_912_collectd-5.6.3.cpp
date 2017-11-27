static int powerdns_get_data(list_item_t *item, char **ret_buffer,
                             size_t *ret_buffer_size) {
  if (item->socktype == SOCK_DGRAM)
    return (powerdns_get_data_dgram(item, ret_buffer, ret_buffer_size));
  else if (item->socktype == SOCK_STREAM)
    return (powerdns_get_data_stream(item, ret_buffer, ret_buffer_size));
  else {
    ERROR("powerdns plugin: Unknown socket type: %i", (int)item->socktype);
    return (-1);
  }
}