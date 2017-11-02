static CURLcode pop3_parse_custom_request(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *custom = data->set.str[STRING_CUSTOMREQUEST];

  /* URL decode the custom request */
  if(custom)
    result = Curl_urldecode(data, custom, 0, &pop3->custom, NULL, TRUE);

  return result;
}