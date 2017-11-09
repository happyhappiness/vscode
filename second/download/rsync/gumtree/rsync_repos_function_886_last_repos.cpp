static char *get_canon_name_from_addr(struct in_addr ip,
				int *perr)
{
	return canon_name_from_hostent(
			gethostbyaddr((void *)&ip, sizeof ip, AF_INET),
			perr);
}