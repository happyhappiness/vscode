static int nut_connect(nut_ups_t *ups) {
  int status, ssl_status;

#if HAVE_UPSCLI_TRYCONNECT
  struct timeval tv;
  tv.tv_sec = connect_timeout / 1000;
  tv.tv_usec = connect_timeout % 1000;

  status =
      upscli_tryconnect(ups->conn, ups->hostname, ups->port, ssl_flags, &tv);
#else /* #if HAVE_UPSCLI_TRYCONNECT */
  status = upscli_connect(ups->conn, ups->hostname, ups->port, ssl_flags);
#endif

  if (status != 0) {
    ERROR("nut plugin: nut_connect: upscli_connect (%s, %i) failed: %s",
          ups->hostname, ups->port, upscli_strerror(ups->conn));
    sfree(ups->conn);
    return -1;
  } /* if (status != 0) */

  INFO("nut plugin: Connection to (%s, %i) established.", ups->hostname,
       ups->port);

  // Output INFO or WARNING based on SSL and VERIFICATION
  ssl_status = upscli_ssl(ups->conn); // 1 for SSL, 0 for not, -1 for error
  if (ssl_status == 1 && verify_peer == 1) {
    INFO("nut plugin: Connection is secured with SSL and certificate "
         "has been verified.");
  } else if (ssl_status == 1) {
    INFO("nut plugin: Connection is secured with SSL with no verification "
         "of server SSL certificate.");
  } else if (ssl_status == 0) {
    WARNING("nut plugin: Connection is unsecured (no SSL).");
  } else {
    ERROR("nut plugin: nut_connect: upscli_ssl failed: %s",
          upscli_strerror(ups->conn));
    sfree(ups->conn);
    return -1;
  } /* if (ssl_status == 1 && verify_peer == 1) */
  return 0;
}