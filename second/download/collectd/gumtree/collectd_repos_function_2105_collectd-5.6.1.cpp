static int get_ti (struct ip_vs_dest_entry *de, char *ti, size_t size)
{
	struct in_addr addr;
	int len = 0;

	if ((NULL == de) || (NULL == ti))
		return 0;

	addr.s_addr = de->addr;

	/* inet_ntoa() returns a pointer to a statically allocated buffer
	 * I hope non-glibc systems behave the same */
	len = ssnprintf (ti, size, "%s_%u", inet_ntoa (addr),
			ntohs (de->port));

	if ((0 > len) || (size <= ((size_t) len))) {
		log_err ("type instance truncated: %s", ti);
		return -1;
	}
	return 0;
}