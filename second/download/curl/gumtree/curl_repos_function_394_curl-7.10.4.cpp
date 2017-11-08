static
CURLcode init_telnet(struct connectdata *conn)
{
  struct TELNET *tn;

  tn = (struct TELNET *)malloc(sizeof(struct TELNET));
  if(!tn)
    return CURLE_OUT_OF_MEMORY;
  
  conn->proto.telnet = (void *)tn; /* make us known */

  memset(tn, 0, sizeof(struct TELNET));

  tn->telrcv_state = CURL_TS_DATA;

  /* Init suboptions */
  CURL_SB_CLEAR(tn);

  /* Set all options to NO */
#if 0
  /* NO is zero => default fill pattern */
  memset(tn->us, CURL_NO, 256);
  memset(tn->usq, CURL_NO, 256);
  memset(tn->us_preferred, CURL_NO, 256);
  memset(tn->him, CURL_NO, 256);
  memset(tn->himq, CURL_NO, 256);
  memset(tn->him_preferred, CURL_NO, 256);
#endif
  /* Set the options we want by default */
  tn->us_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->us_preferred[CURL_TELOPT_SGA] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_BINARY] = CURL_YES;
  tn->him_preferred[CURL_TELOPT_SGA] = CURL_YES;

  return CURLE_OK;
}