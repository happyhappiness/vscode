static
CURLcode init_telnet(struct connectdata *conn)
{
  struct TELNET *tn;

  tn = (struct TELNET *)malloc(sizeof(struct TELNET));
  if(!tn)
    return CURLE_OUT_OF_MEMORY;
  
  conn->proto.telnet = (void *)tn; /* make us known */

  memset(tn, 0, sizeof(struct TELNET));

  tn->telrcv_state = TS_DATA;

  /* Init suboptions */
  SB_CLEAR(tn);

  /* Set all options to NO */
#if 0
  /* NO is zero => default fill pattern */
  memset(tn->us, NO, 256);
  memset(tn->usq, NO, 256);
  memset(tn->us_preferred, NO, 256);
  memset(tn->him, NO, 256);
  memset(tn->himq, NO, 256);
  memset(tn->him_preferred, NO, 256);
#endif
  /* Set the options we want by default */
  tn->us_preferred[TELOPT_BINARY] = YES;
  tn->us_preferred[TELOPT_SGA] = YES;
  tn->him_preferred[TELOPT_BINARY] = YES;
  tn->him_preferred[TELOPT_SGA] = YES;

  return CURLE_OK;
}