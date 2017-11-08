CURLcode Curl_done(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  CURLcode result;

  /* cleanups done even if the connection is re-used */

  if(conn->bits.rangestringalloc) {
    free(conn->range);
    conn->bits.rangestringalloc = FALSE;
  }

  /* Cleanup possible redirect junk */
  if(conn->newurl) {
    free(conn->newurl);
    conn->newurl = NULL;
  }

  if(conn->connect_addr)
    Curl_resolv_unlock(conn->data, conn->connect_addr); /* done with this */

#if defined(MALLOCDEBUG) && defined(AGGRESIVE_TEST)
  /* scan for DNS cache entries still marked as in use */
  Curl_hash_apply(data->hostcache,
                  NULL, Curl_scan_cache_used);
#endif

  /* this calls the protocol-specific function pointer previously set */
  if(conn->curl_done)
    result = conn->curl_done(conn);
  else
    result = CURLE_OK;

  Curl_pgrsDone(conn); /* done with the operation */

  /* if data->set.reuse_forbid is TRUE, it means the libcurl client has
     forced us to close this no matter what we think.

     if conn->bits.close is TRUE, it means that the connection should be
     closed in spite of all our efforts to be nice, due to protocol
     restrictions in our or the server's end */
  if(data->set.reuse_forbid ||
     ((CURLE_OK == result) && conn->bits.close))
    result = Curl_disconnect(conn); /* close the connection */
  else
    infof(data, "Connection #%d left intact\n", conn->connectindex);

  return result;
}