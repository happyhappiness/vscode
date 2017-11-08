static   
void rec_dont(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->us[option])
  {
    case NO:
      /* Already disabled */
      break;
	 
    case YES:
      tn->us[option] = NO;
      send_negotiation(conn, WONT, option);
      break;
	 
    case WANTNO:
      switch(tn->usq[option])
      {
        case EMPTY:
          tn->us[option] = NO;
          break;
	 
        case OPPOSITE:
          tn->us[option] = WANTYES;
          tn->usq[option] = EMPTY;
          send_negotiation(conn, WILL, option);
          break;
      }
      break;
	 
    case WANTYES:
      switch(tn->usq[option])
      {
        case EMPTY:
          tn->us[option] = NO;
          break;
        case OPPOSITE:
          tn->us[option] = NO;
          tn->usq[option] = EMPTY;
          break;
      }
      break;
  }
}