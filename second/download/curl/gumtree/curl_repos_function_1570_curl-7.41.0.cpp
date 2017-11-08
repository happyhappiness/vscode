static CURLcode pop3_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;

  *done = FALSE; /* default to false */

  /* Parse the URL path */
  result = pop3_parse_url_path(conn);
  if(result)
    return result;

  /* Parse the custom request */
  result = pop3_parse_custom_request(conn);
  if(result)
    return result;

  result = pop3_regular_transfer(conn, done);

  return result;
}