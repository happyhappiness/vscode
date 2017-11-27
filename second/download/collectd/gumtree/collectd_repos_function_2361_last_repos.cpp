static int cipvs_read(void) {
  if (sockfd < 0)
    return -1;

  struct ip_vs_get_services *services = ipvs_get_services();
  if (services == NULL)
    return -1;

  for (size_t i = 0; i < services->num_services; ++i)
    cipvs_submit_service(&services->entrytable[i]);

  free(services);
  return 0;
}