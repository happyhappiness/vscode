static int get_ti(struct ip_vs_dest_entry *de, char *ti, size_t size) {
  if ((de == NULL) || (ti == NULL))
    return 0;

  struct in_addr addr = {.s_addr = de->addr};

  int len = snprintf(ti, size, "%s_%u", inet_ntoa(addr), ntohs(de->port));

  if ((len < 0) || (size <= ((size_t)len))) {
    log_err("type instance truncated: %s", ti);
    return -1;
  }
  return 0;
}