{
    /* only realloc if there was a length */
    len = ntohl(len);
    tmp = Curl_saferealloc(buf->data, len);
  }