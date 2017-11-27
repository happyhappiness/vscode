static int ovs_db_data_send(const ovs_db_t *pdb, const char *data, size_t len) {
  ssize_t nbytes = 0;
  size_t rem = len;
  size_t off = 0;

  while (rem > 0) {
    if ((nbytes = send(pdb->sock, data + off, rem, 0)) <= 0)
      return -1;
    rem -= (size_t)nbytes;
    off += (size_t)nbytes;
  }
  return 0;
}