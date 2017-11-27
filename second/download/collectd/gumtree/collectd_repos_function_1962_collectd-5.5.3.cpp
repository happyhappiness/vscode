static int cipvs_read (void)
{
	struct ip_vs_get_services *services = NULL;
	int i = 0;

	if (sockfd < 0)
		return (-1);

	if (NULL == (services = ipvs_get_services ()))
		return -1;

	for (i = 0; i < services->num_services; ++i)
		cipvs_submit_service (&services->entrytable[i]);

	free (services);
	return 0;
}