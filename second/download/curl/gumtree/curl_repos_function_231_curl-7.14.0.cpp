CURLcode Curl_is_resolved(struct connectdata *conn,
                          struct Curl_dns_entry **entry)
{
  *entry = NULL;

  if (conn->async.done) {
    /* we're done */
    Curl_destroy_thread_data(&conn->async);
    if (!conn->async.dns) {
      TRACE(("Curl_is_resolved(): CURLE_COULDNT_RESOLVE_HOST\n"));
      return CURLE_COULDNT_RESOLVE_HOST;
    }
    *entry = conn->async.dns;
    TRACE(("resolved okay, dns %p\n", *entry));
  }
  return CURLE_OK;
}