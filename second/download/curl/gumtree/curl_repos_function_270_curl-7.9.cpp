static
void set_remote_option(struct connectdata *conn, int option, int newstate)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  if(newstate == YES)
  {
    switch(tn->him[option])
    {
      case NO:
        tn->him[option] = WANTYES;
        send_negotiation(conn, DO, option);
        break;
	 
      case YES:
        /* Already enabled */
        break;
	 
      case WANTNO:
        switch(tn->himq[option])
        {
          case EMPTY:
            /* Already negotiating for YES, queue the request */
            tn->himq[option] = OPPOSITE;
            break;
          case OPPOSITE:
            /* Error: already queued an enable request */
            break;
        }
        break;
	 
      case WANTYES:
        switch(tn->himq[option])
        {
          case EMPTY:
            /* Error: already negotiating for enable */
            break;
          case OPPOSITE:
            tn->himq[option] = EMPTY;
            break;
        }
        break;
    }
  }
  else /* NO */
  {
    switch(tn->him[option])
    {
      case NO:
        /* Already disabled */
        break;
	 
      case YES:
        tn->him[option] = WANTNO;
        send_negotiation(conn, DONT, option);
        break;
	 
      case WANTNO:
        switch(tn->himq[option])
        {
          case EMPTY:
            /* Already negotiating for NO */
            break;
          case OPPOSITE:
            tn->himq[option] = EMPTY;
            break;
        }
        break;
	 
      case WANTYES:
        switch(tn->himq[option])
        {
          case EMPTY:
            tn->himq[option] = OPPOSITE;
            break;
          case OPPOSITE:
            break;
        }
        break;
    }
  }
}