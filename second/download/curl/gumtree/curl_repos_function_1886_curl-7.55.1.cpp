static char *control_address(struct connectdata *conn)
{
  /* Returns the control connection IP address.
     If a proxy tunnel is used, returns the original host name instead, because
     the effective control connection address is the proxy address,
     not the ftp host. */
  if(conn->bits.tunnel_proxy || conn->bits.socksproxy)
    return conn->host.name;

  return conn->ip_addr_str;
}