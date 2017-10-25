static CURLcode add_custom_headers(struct connectdata *conn,
                                   send_buffer *req_buffer)
{
  CURLcode result = CURLE_OK;
  char *ptr;
  struct curl_slist *headers=conn->data->set.headers;

  while(headers) {
    ptr = strchr(headers->data, ':');
    if(ptr) {
      /* we require a colon for this to be a true header */

      ptr++; /* pass the colon */
      while(*ptr && isspace((int)*ptr))
        ptr++;

      if(*ptr) {
        /* only send this if the contents was non-blank */

        if(conn->allocptr.host &&
           /* a Host: header was sent already, don't pass on any custom Host:
              header as that will produce *two* in the same request! */
           curl_strnequal("Host:", headers->data, 5))
          ;
        else {

          result = add_bufferf(req_buffer, "%s\r\n", headers->data);
          if(result)
            return result;
        }
      }
    }
    headers = headers->next;
  }
  return result;
}