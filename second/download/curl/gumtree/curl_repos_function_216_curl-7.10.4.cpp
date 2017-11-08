static
CURLcode add_buffer_send(send_buffer *in,
                         int sockfd,
                         struct connectdata *conn,
                         long *bytes_written) /* add the number of sent
                                                 bytes to this counter */
{
  ssize_t amount;
  CURLcode res;
  char *ptr;
  int size;
  struct HTTP *http = conn->proto.http;

  /* The looping below is required since we use non-blocking sockets, but due
     to the circumstances we will just loop and try again and again etc */

  ptr = in->buffer;
  size = in->size_used;

  res = Curl_write(conn, sockfd, ptr, size, &amount);

  if(CURLE_OK == res) {

    if(conn->data->set.verbose)
      /* this data _may_ contain binary stuff */
      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr, amount);

    *bytes_written += amount;
    
    if(amount != size) {
      /* The whole request could not be sent in one system call. We must queue
         it up and send it later when we get the chance. We must not loop here
         and wait until it might work again. */

      size -= amount;
      ptr += amount;
    
      /* backup the currently set pointers */
      http->backup.fread = conn->fread;
      http->backup.fread_in = conn->fread_in;
      http->backup.postdata = http->postdata;
      http->backup.postsize = http->postsize;

      /* set the new pointers for the request-sending */
      conn->fread = (curl_read_callback)readmoredata;
      conn->fread_in = (void *)conn;
      http->postdata = ptr;
      http->postsize = size;

      http->send_buffer = in;
      http->sending = HTTPSEND_REQUEST;
      
      return CURLE_OK;
    }
    http->sending = HTTPSEND_BODY;
    /* the full buffer was sent, clean up and return */
  }
  if(in->buffer)
    free(in->buffer);
  free(in);

  return res;
}