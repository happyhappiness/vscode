static int cipvs_init(void) {
  struct ip_vs_getinfo ipvs_info;

  if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1) {
    char errbuf[1024];
    log_err("cipvs_init: socket() failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  socklen_t len = sizeof(ipvs_info);

  if (getsockopt(sockfd, IPPROTO_IP, IP_VS_SO_GET_INFO, &ipvs_info, &len) ==
      -1) {
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