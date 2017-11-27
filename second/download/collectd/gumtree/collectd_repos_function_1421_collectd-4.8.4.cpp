static struct ip_vs_get_dests *ipvs_get_dests (struct ip_vs_service_entry *se)
{
	struct ip_vs_get_dests *ret;
	socklen_t len;

	len = sizeof (*ret) + sizeof (struct ip_vs_dest_entry) * se->num_dests;

	if (NULL == (ret = malloc (len))) {
		log_err ("ipvs_get_dests: Out of memory.");
		exit (3);
	}

	ret->fwmark    = se->fwmark;
	ret->protocol  = se->protocol;
	ret->addr      = se->addr;
	ret->port      = se->port;
	ret->num_dests = se->num_dests;

	if (0 != getsockopt (sockfd, IPPROTO_IP, IP_VS_SO_GET_DESTS,
				(void *)ret, &len)) {
		char errbuf[1024];
		log_err ("ipvs_get_dests: getsockopt() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		free (ret);
		return NULL;
	}
	return ret;
}