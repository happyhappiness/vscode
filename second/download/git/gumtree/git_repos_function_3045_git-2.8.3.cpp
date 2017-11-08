static const char *get_ip_address(struct hostinfo *hi)
{
	lookup_hostname(hi);
	return hi->ip_address.buf;
}