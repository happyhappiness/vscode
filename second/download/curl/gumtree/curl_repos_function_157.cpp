void set_remote_option(struct UrlData *data, int option, int newstate)
{
   if(newstate == YES)
   {
      switch(him[option])
      {
      case NO:
	 him[option] = WANTYES;
	 send_negotiation(data, DO, option);
	 break;
	 
      case YES:
	 /* Already enabled */
	 break;
	 
      case WANTNO:
	 switch(himq[option])
	 {
	 case EMPTY:
	    /* Already negotiating for YES, queue the request */
	    himq[option] = OPPOSITE;
	    break;
	 case OPPOSITE:
	    /* Error: already queued an enable request */
	    break;
	 }
	 break;
	 
      case WANTYES:
	 switch(himq[option])
	 {
	 case EMPTY:
	    /* Error: already negotiating for enable */
	    break;
	 case OPPOSITE:
	    himq[option] = EMPTY;
	    break;
	 }
	 break;
      }
   }
   else /* NO */
   {
      switch(him[option])
      {
      case NO:
	 /* Already disabled */
	 break;
	 
      case YES:
	 him[option] = WANTNO;
	 send_negotiation(data, DONT, option);
	 break;
	 
      case WANTNO:
	 switch(himq[option])
	 {
	 case EMPTY:
	    /* Already negotiating for NO */
	    break;
	 case OPPOSITE:
	    himq[option] = EMPTY;
	    break;
	 }
	 break;
	 
      case WANTYES:
	 switch(himq[option])
	 {
	 case EMPTY:
	    himq[option] = OPPOSITE;
	    break;
	 case OPPOSITE:
	    break;
	 }
	 break;
      }
   }
}