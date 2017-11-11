static const char *ip2str(int family, struct sockaddr *sin, socklen_t len)
{
#ifdef NO_IPV6
	static char ip[INET_ADDRSTRLEN];
#else
	static char ip[INET6_ADDRSTRLEN];
#endif

	switch (family) {
#ifndef NO_IPV6
	case AF_INET6:
		inet_ntop(family, &((struct sockaddr_in6*)sin)->sin6_addr, ip, len);
		break;
#endif
	case AF_INET:
		inet_ntop(family, &((struct sockaddr_in*)sin)->sin_addr, ip, len);
		break;
	default:
		xsnprintf(ip, sizeof(ip), "<unknown>");
	}
	return ip;
}