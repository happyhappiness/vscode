static char *control_address(struct connectdata *conn)
{
  /* Returns the control connection IP address.
     If a proxy tunnel is used, returns the original host name instead, because
     the effective control connection address is the proxy address,
     not the ftp host. */
  if(conn->bits.tunnel_proxy ||
     conn->proxytype == CURLPROXY_SOCKS5 ||
     conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
     conn->proxytype == CURLPROXY_SOCKS4 ||
     conn->proxytype == CURLPROXY_SOCKS4A)
    return conn->host.name;

  return conn->ip_addr_str;
}