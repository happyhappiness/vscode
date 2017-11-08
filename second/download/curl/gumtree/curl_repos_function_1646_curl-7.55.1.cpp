CURLcode Curl_client_write(struct connectdata *conn,
                           int type,
                           char *ptr,
                           size_t len)
{
  struct Curl_easy *data = conn->data;

  if(0 == len)
    len = strlen(ptr);

  DEBUGASSERT(type <= 3);

  /* FTP data may need conversion. */
  if((type & CLIENTWRITE_BODY) &&
    (conn->handler->protocol & PROTO_FAMILY_FTP) &&
    conn->proto.ftpc.transfertype == 'A') {
    /* convert from the network encoding */
    CURLcode result = Curl_convert_from_network(data, ptr, len);
    /* Curl_convert_from_network calls failf if unsuccessful */
    if(result)
      return result;

#ifdef CURL_DO_LINEEND_CONV
    /* convert end-of-line markers */
    len = convert_lineends(data, ptr, len);
#endif /* CURL_DO_LINEEND_CONV */
    }

  return Curl_client_chop_write(conn, type, ptr, len);
}