CURLcode Curl_add_custom_headers(struct connectdata *conn,
                                   Curl_send_buffer *req_buffer)
{
  char *ptr;
  struct curl_slist *headers=conn->data->set.headers;

  while(headers) {
    ptr = strchr(headers->data, ':');
    if(ptr) {
      /* we require a colon for this to be a true header */

      ptr++; /* pass the colon */
      while(*ptr && ISSPACE(*ptr))
        ptr++;

      if(*ptr) {
        /* only send this if the contents was non-blank */

        if(conn->allocptr.host &&
           /* a Host: header was sent already, don't pass on any custom Host:
              header as that will produce *two* in the same request! */
           checkprefix("Host:", headers->data))
          ;
        else if(conn->data->set.httpreq == HTTPREQ_POST_FORM &&
                /* this header (extended by formdata.c) is sent later */
                checkprefix("Content-Type:", headers->data))
          ;
        else if(conn->bits.authneg &&
                /* while doing auth neg, don't allow the custom length since
                   we will force length zero then */
                checkprefix("Content-Length", headers->data))
          ;
        else if(conn->allocptr.te &&
                /* when asking for Transfer-Encoding, don't pass on a custom
                   Connection: */
                checkprefix("Connection", headers->data))
          ;
        else {
          CURLcode result = Curl_add_bufferf(req_buffer, "%s\r\n",
                                             headers->data);
          if(result)
            return result;
        }
      }
    }
    else {
      ptr = strchr(headers->data, ';');
      if(ptr) {

        ptr++; /* pass the semicolon */
        while(*ptr && ISSPACE(*ptr))
          ptr++;

        if(*ptr) {
          /* this may be used for something else in the future */
        }
        else {
          if(*(--ptr) == ';') {
            CURLcode result;

            /* send no-value custom header if terminated by semicolon */
            *ptr = ':';
            result = Curl_add_bufferf(req_buffer, "%s\r\n",
                                             headers->data);
            if(result)
              return result;
          }
        }
      }
    }
    headers = headers->next;
  }
  return CURLE_OK;
}