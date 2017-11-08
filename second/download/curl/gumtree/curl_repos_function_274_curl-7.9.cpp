static
void rec_do(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->us[option])
  {
    case NO:
      if(tn->us_preferred[option] == YES)
      {
        tn->us[option] = YES;
        send_negotiation(conn, WILL, option);
      }
      else
      {
        send_negotiation(conn, WONT, option);
      }
      break;
	 
    case YES:
      /* Already enabled */
      break;
	 
    case WANTNO:
      switch(tn->usq[option])
      {
        case EMPTY:
          /* Error: DONT answered by WILL */
          tn->us[option] = NO;
          break;
        case OPPOSITE:
          /* Error: DONT answered by WILL */
          tn->us[option] = YES;
          tn->usq[option] = EMPTY;
          break;
      }
      break;
	 
    case WANTYES:
      switch(tn->usq[option])
      {
        case EMPTY:
          tn->us[option] = YES;
          break;
        case OPPOSITE:
          tn->us[option] = WANTNO;
          tn->himq[option] = EMPTY;
          send_negotiation(conn, WONT, option);
          break;
      }
      break;
  }
}