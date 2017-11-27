static struct ip_vs_get_dests *ipvs_get_dests(struct ip_vs_service_entry *se) {
  struct ip_vs_get_dests *dests;

  socklen_t len =
      sizeof(*dests) + sizeof(struct ip_vs_dest_entry) * se->num_dests;

  dests = malloc(len);
  if (dests == NULL) {
    log_err("ipvs_get_dests: Out of memory.");
    return NULL;
  }

  dests->fwmark = se->fwmark;
  dests->protocol = se->protocol;
  dests->addr = se->addr;
  dests->port = se->port;
  dests->num_dests = se->num_dests;

  if (getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_DESTS, dests, &len) == -1) {
    char errbuf[1024];
    log_err("ipvs_get_dests: getsockopt() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    free(dests);
    return NULL;
  }
  return dests;
}