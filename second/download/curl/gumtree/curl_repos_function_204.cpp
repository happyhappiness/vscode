CURLcode Curl_store_ip_addr(struct connectdata *conn)
{
  char addrbuf[256];
  Curl_printable_address(conn->ip_addr, addrbuf, sizeof(addrbuf));

  /* save the string */
  Curl_safefree(conn->ip_addr_str);
  conn->ip_addr_str = strdup(addrbuf);
  if(!conn->ip_addr_str)
    return CURLE_OUT_OF_MEMORY; /* FAIL */

#ifdef PF_INET6
  if(conn->ip_addr->ai_family == PF_INET6)
    conn->bits.ipv6 = TRUE;
#endif

  return CURLE_OK;
}