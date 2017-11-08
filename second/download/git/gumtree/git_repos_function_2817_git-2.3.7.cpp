static const char *get_ip_address(void)
{
	lookup_hostname();
	return ip_address;
}