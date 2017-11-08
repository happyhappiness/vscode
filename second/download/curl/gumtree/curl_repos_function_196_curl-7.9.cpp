static 
CURLcode _ftp_sendquote(struct connectdata *conn, struct curl_slist *quote)
{
  struct curl_slist *item;
  ssize_t            nread;
  int                ftpcode;

  item = quote;
  while (item) {
    if (item->data) {
      ftpsendf(conn->firstsocket, conn, "%s", item->data);

      nread = Curl_GetFTPResponse(conn->firstsocket, 
                                  conn->data->state.buffer, conn, &ftpcode);
      if (nread < 0)
        return CURLE_OPERATION_TIMEOUTED;

      if (ftpcode >= 400) {
        failf(conn->data, "QUOT string not accepted: %s", item->data);
        return CURLE_FTP_QUOTE_ERROR;
      }
    }

    item = item->next;
  }

  return CURLE_OK;
}