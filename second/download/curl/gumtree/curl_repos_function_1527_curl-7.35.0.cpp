bool Curl_ipvalid(struct connectdata *conn)
{
  if(conn->ip_version == CURL_IPRESOLVE_V6)
    /* an ipv6 address was requested and we can't get/use one */
    return FALSE;

  return TRUE; /* OK, proceed */
}