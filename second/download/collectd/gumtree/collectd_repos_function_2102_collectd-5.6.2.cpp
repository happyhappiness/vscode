static struct ip_vs_get_services *ipvs_get_services(void) {
  struct ip_vs_getinfo ipvs_info;
  struct ip_vs_get_services *ret;

  socklen_t len;

  len = sizeof(ipvs_info);

  if (0 != getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_INFO, (void *)&ipvs_info,
                      &len)) {
    char errbuf[1024];
    log_err("ip_vs_get_services: getsockopt() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return NULL;
  }

  len = sizeof(*ret) +
        sizeof(struct ip_vs_service_entry) * ipvs_info.num_services;

  if (NULL == (ret = malloc(len))) {
    log_err("ipvs_get_services: Out of memory.");
    exit(3);
  }

  ret->num_services = ipvs_info.num_services;

  if (0 != getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_SERVICES, (void *)ret,
                      &len)) {
    char errbuf[1024];
    log_err("ipvs_get_services: getsockopt failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));

    free(ret);
    return NULL;
  }
  return ret;
}