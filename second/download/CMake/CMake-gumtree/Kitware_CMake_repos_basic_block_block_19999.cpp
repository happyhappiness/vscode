{
  if (ttl < 1 || ttl > 255)
    return -EINVAL;

#if defined(__MVS__)
  if (!(handle->flags & UV_HANDLE_IPV6))
    return -ENOTSUP;  /* zOS does not support setting ttl for IPv4 */
#endif

/*
 * On Solaris and derivatives such as SmartOS, the length of socket options
 * is sizeof(int) for IP_TTL and IPV6_UNICAST_HOPS,
 * so hardcode the size of these options on this platform,
 * and use the general uv__setsockopt_maybe_char call on other platforms.
 */
#if defined(__sun) || defined(_AIX) || defined(__OpenBSD__) || \
    defined(__MVS__)

  return uv__setsockopt(handle,
                        IP_TTL,
                        IPV6_UNICAST_HOPS,
                        &ttl,
                        sizeof(ttl));
#endif /* defined(__sun) || defined(_AIX) || defined (__OpenBSD__) ||
          defined(__MVS__) */

  return uv__setsockopt_maybe_char(handle,
                                   IP_TTL,
                                   IPV6_UNICAST_HOPS,
                                   ttl);
}