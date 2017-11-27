static int get_pi (struct ip_vs_service_entry *se, char *pi, size_t size)
{
	struct in_addr addr;
	int len = 0;

	if ((NULL == se) || (NULL == pi))
		return 0;

	addr.s_addr = se->addr;

	/* inet_ntoa() returns a pointer to a statically allocated buffer
	 * I hope non-glibc systems behave the same */
	len = ssnprintf (pi, size, "%s_%s%u", inet_ntoa (addr),
			(se->protocol == IPPROTO_TCP) ? "TCP" : "UDP",
			ntohs (se->port));

	if ((0 > len) || (size <= ((size_t) len))) {
		log_err ("plugin instance truncated: %s", pi);
		return -1;
	}
	return 0;
}