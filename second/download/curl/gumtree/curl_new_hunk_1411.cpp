 * add_buffer_send() sends a buffer and frees all associated memory.
 */
static
size_t add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in)
{
  size_t amount;
  if(conn->data->set.verbose) {
    fputs("> ", conn->data->set.err);
    /* this data _may_ contain binary stuff */
    fwrite(in->buffer, in->size_used, 1, conn->data->set.err);
  }

  Curl_write(conn, sockfd, in->buffer, in->size_used, &amount);

  if(in->buffer)
    free(in->buffer);
