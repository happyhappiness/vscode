CURLcode Curl_resolver_wait_resolv(struct connectdata *conn,
                                   struct Curl_dns_entry **entry)
{
  struct thread_data   *td = (struct thread_data*) conn->async.os_specific;
  CURLcode result = CURLE_OK;

  DEBUGASSERT(conn && td);

  /* wait for the thread to resolve the name */
  if(Curl_thread_join(&td->thread_hnd))
    result = getaddrinfo_complete(conn);
  else
    DEBUGASSERT(0);

  conn->async.done = TRUE;

  if(entry)
    *entry = conn->async.dns;

  if(!conn->async.dns)
    /* a name was not resolved, report error */
    result = resolver_error(conn);

  destroy_async_data(&conn->async);

  if(!conn->async.dns)
    connclose(conn, "asynch resolve failed");

  return result;
}