void init_telnet(struct UrlData *data)
{
   telrcv_state = TS_DATA;

   /* Init suboptions */
   SB_CLEAR();

   /* Set all options to NO */
   memset(us, NO, 256);
   memset(usq, NO, 256);
   memset(us_preferred, NO, 256);
   memset(him, NO, 256);
   memset(himq, NO, 256);
   memset(him_preferred, NO, 256);

   /* Set the options we want */
   us_preferred[TELOPT_BINARY] = YES;
   us_preferred[TELOPT_SGA] = YES;
   him_preferred[TELOPT_BINARY] = YES;
   him_preferred[TELOPT_SGA] = YES;

   /* Start negotiating */
   negotiate(data);
}