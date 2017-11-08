static void negotiate(struct connectdata *conn)
{
  int i;
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
   
  for(i = 0;i < NTELOPTS;i++)
  {
    if(tn->us_preferred[i] == YES)
      set_local_option(conn, i, YES);
      
    if(tn->him_preferred[i] == YES)
      set_remote_option(conn, i, YES);
  }
}