static struct ip_vs_get_services *ipvs_get_services(void) {
  struct ip_vs_getinfo ipvs_info;
  struct ip_vs_get_services *services;

  socklen_t len = sizeof(ipvs_info);

  if (getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_INFO, &ipvs_info, &len) ==
      -1) {
    char errbuf[1024];
    log_err("ip_vs_get_services: getsockopt() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return NULL;
  }

  len = sizeof(*services) +
        sizeof(struct ip_vs_service_entry) * ipvs_info.num_services;

  services = malloc(len);
  if (services == NULL) {
    log_err("ipvs_get_services: Out of memory.");
    return NULL;
  }

  services->num_services = ipvs_info.num_services;

  if (getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_SERVICES, services, &len) ==
      -1) {
    char errbuf[1024];
    log_err("ipvs_get_services: getsockopt failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));

    free(services);
    return NULL;
  }
  return services;
}