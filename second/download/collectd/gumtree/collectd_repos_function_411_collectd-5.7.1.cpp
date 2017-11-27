static int apcups_shutdown(void) {
  if (global_sockfd < 0)
    return (0);

  net_shutdown(&global_sockfd);
  return (0);
}