static inline int
unconditional(const struct ip6t_ip6 *ipv6)
{
	unsigned int i;

	for (i = 0; i < sizeof(*ipv6); i++)
		if (((char *)ipv6)[i])
			break;

	return (i == sizeof(*ipv6));
}