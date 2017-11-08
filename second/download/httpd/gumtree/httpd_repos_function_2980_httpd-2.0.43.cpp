const char *
apr_inet_ntop(int af, const void *src, char *dst, apr_size_t size)
{
	switch (af) {
	case AF_INET:
		return (inet_ntop4(src, dst, size));
#if APR_HAVE_IPV6
	case AF_INET6:
		return (inet_ntop6(src, dst, size));
#endif
	default:
		errno = EAFNOSUPPORT;
		return (NULL);
	}
	/* NOTREACHED */
}