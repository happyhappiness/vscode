static int cipvs_init(void) {
  struct ip_vs_getinfo ipvs_info;

  socklen_t len;

  if (-1 == (sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))) {
    char errbuf[1024];
    log_err("cipvs_init: socket() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  len = sizeof(ipvs_info);

  if (0 != getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_INFO, (void *)&ipvs_info,
                      &len)) {
    char errbuf[1024];
    log_err("cipvs_init: getsockopt() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    close(sockfd);
    sockfd = -1;
    return -1;
  }

  /* we need IPVS >= 1.1.4 */
  if (ipvs_info.version < ((1 << 16) + (1 << 8) + 4)) {
    log_err("cipvs_init: IPVS version too old (%d.%d.%d < %d.%d.%d)",
            NVERSION(ipvs_info.version), 1, 1, 4);
    close(sockfd);
    sockfd = -1;
    return -1;
  } else {
    log_info("Successfully connected to IPVS %d.%d.%d",
             NVERSION(ipvs_info.version));
  }
  return 0;
}