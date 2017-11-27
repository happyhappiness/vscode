int
ipv6_prefix_length(const struct in6_addr *a)
{
	int l, i;
	for (l = 0; l < 128; l++) {
		if (BIT6(a, l) == 0)
			break;
	}
	for (i = l + 1; i < 128; i++) {
		if (BIT6(a, i) == 1)
			return -1;
	}
	return l;
}