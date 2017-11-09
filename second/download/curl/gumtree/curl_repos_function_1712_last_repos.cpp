static CURLcode pop3_setup_connection(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;

  /* Initialise the POP3 layer */
  CURLcode result = pop3_init(conn);
  if(result)
    return result;

  /* Clear the TLS upgraded flag */
  conn->tls_upgraded = FALSE;
  data->state.path++;   /* don't include the initial slash */

  return CURLE_OK;
}