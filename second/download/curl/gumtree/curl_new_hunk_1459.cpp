}

/*
 * add_buffer_send() sends a buffer and frees all associated memory.
 */
static
CURLcode add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in,
                         long *bytes_written)
{
  ssize_t amount;
  CURLcode res;
  char *ptr;
  int size;

  /* The looping below is required since we use non-blocking sockets, but due
     to the circumstances we will just loop and try again and again etc */

  ptr = in->buffer;
  size = in->size_used;
  do {
    res = Curl_write(conn, sockfd, ptr, size, &amount);

    if(CURLE_OK != res)
      break;

    if(conn->data->set.verbose)
      /* this data _may_ contain binary stuff */
      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr, amount);

    if(amount != size) {
      size -= amount;
      ptr += amount;
    }
    else
      break;

  } while(1);

  if(in->buffer)
    free(in->buffer);
  free(in);

  *bytes_written += amount;

  return res;
}


/* 
 * add_bufferf() builds a buffer from the formatted input
 */
