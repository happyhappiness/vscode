void set_local_option(struct connectdata *conn, int option, int newstate)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  if(newstate == YES)
  {
    switch(tn->us[option])
    {
      case NO:
        tn->us[option] = WANTYES;
        send_negotiation(conn, WILL, option);
        break;
	 
      case YES:
        /* Already enabled */
        break;
	 
      case WANTNO:
        switch(tn->usq[option])
        {
          case EMPTY:
            /* Already negotiating for YES, queue the request */
            tn->usq[option] = OPPOSITE;
            break;
          case OPPOSITE:
            /* Error: already queued an enable request */
            break;
        }
        break;
	 
      case WANTYES:
        switch(tn->usq[option])
        {
          case EMPTY:
            /* Error: already negotiating for enable */
            break;
          case OPPOSITE:
            tn->usq[option] = EMPTY;
            break;
        }
        break;
    }
  }
  else /* NO */
  {
    switch(tn->us[option])
    {
      case NO:
        /* Already disabled */
        break;
	 
      case YES:
        tn->us[option] = WANTNO;
        send_negotiation(conn, WONT, option);
        break;
	 
      case WANTNO:
        switch(tn->usq[option])
        {
          case EMPTY:
            /* Already negotiating for NO */
            break;
          case OPPOSITE:
            tn->usq[option] = EMPTY;
            break;
        }
        break;
	 
      case WANTYES:
        switch(tn->usq[option])
        {
          case EMPTY:
            tn->usq[option] = OPPOSITE;
            break;
          case OPPOSITE:
            break;
        }
        break;
    }
  }
}