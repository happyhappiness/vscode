static
CURLcode init_telnet(struct connectdata *conn)
{
  struct TELNET *tn;

  tn = (struct TELNET *)calloc(1, sizeof(struct TELNET));
  if(!tn)
    return CURLE_OUT_OF_MEMORY;

  conn->proto.telnet = (void *)tn; /* make us known */

  tn->telrcv_state = CURL_TS_DATA;

  /* Init suboptions */
  CURL_SB_CLEAR(tn);

  /* Set the options we want by default */
  tn->us_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->us_preferred[CURL_TELOPT_SGA] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_SGA] = CURL_YES;

  return CURLE_OK;
}