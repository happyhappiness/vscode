static int get_pi(struct ip_vs_service_entry *se, char *pi, size_t size) {
  if ((se == NULL) || (pi == NULL))
    return 0;

  struct in_addr addr = {.s_addr = se->addr};

  int len =
      snprintf(pi, size, "%s_%s%u", inet_ntoa(addr),
               (se->protocol == IPPROTO_TCP) ? "TCP" : "UDP", ntohs(se->port));

  if ((len < 0) || (size <= ((size_t)len))) {
    log_err("plugin instance truncated: %s", pi);
    return -1;
  }
  return 0;
}