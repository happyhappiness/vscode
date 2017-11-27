static inline int ignore_list_match(const struct in6_addr *addr) {
  for (ip_list_t *ptr = IgnoreList; ptr != NULL; ptr = ptr->next)
    if (cmp_in6_addr(addr, &ptr->addr) == 0)
      return (1);
  return (0);
}