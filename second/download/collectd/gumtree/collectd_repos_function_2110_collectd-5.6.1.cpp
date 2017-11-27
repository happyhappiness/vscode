static int cipvs_read (void)
{
	struct ip_vs_get_services *services = NULL;

	if (sockfd < 0)
		return (-1);

	if (NULL == (services = ipvs_get_services ()))
		return -1;

	for (size_t i = 0; i < services->num_services; ++i)
		cipvs_submit_service (&services->entrytable[i]);

	free (services);
	return 0;
}