static
void rec_will(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->him[option])
  {
    case NO:
      if(tn->him_preferred[option] == YES)
      {
        tn->him[option] = YES;
        send_negotiation(conn, DO, option);
      }
      else
      {
        send_negotiation(conn, DONT, option);
      }
      break;
	 
    case YES:
      /* Already enabled */
      break;
	 
    case WANTNO:
      switch(tn->himq[option])
      {
        case EMPTY:
          /* Error: DONT answered by WILL */
          tn->him[option] = NO;
          break;
        case OPPOSITE:
          /* Error: DONT answered by WILL */
          tn->him[option] = YES;
          tn->himq[option] = EMPTY;
          break;
      }
      break;
	 
    case WANTYES:
      switch(tn->himq[option])
      {
        case EMPTY:
          tn->him[option] = YES;
          break;
        case OPPOSITE:
          tn->him[option] = WANTNO;
          tn->himq[option] = EMPTY;
          send_negotiation(conn, DONT, option);
          break;
      }
      break;
  }
}