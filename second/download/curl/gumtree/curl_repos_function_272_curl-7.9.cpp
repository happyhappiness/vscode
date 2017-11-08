static
void rec_wont(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->him[option])
  {
    case NO:
      /* Already disabled */
      break;
	 
    case YES:
      tn->him[option] = NO;
      send_negotiation(conn, DONT, option);
      break;
	 
    case WANTNO:
      switch(tn->himq[option])
      {
        case EMPTY:
          tn->him[option] = NO;
          break;
	 
        case OPPOSITE:
          tn->him[option] = WANTYES;
          tn->himq[option] = EMPTY;
          send_negotiation(conn, DO, option);
          break;
      }
      break;
	 
    case WANTYES:
      switch(tn->himq[option])
      {
        case EMPTY:
          tn->him[option] = NO;
          break;
        case OPPOSITE:
          tn->him[option] = NO;
          tn->himq[option] = EMPTY;
          break;
      }
      break;
  }
}