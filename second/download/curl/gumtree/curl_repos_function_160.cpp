void set_local_option(struct UrlData *data, int option, int newstate)
{
   if(newstate == YES)
   {
      switch(us[option])
      {
      case NO:
	 us[option] = WANTYES;
	 send_negotiation(data, WILL, option);
	 break;
	 
      case YES:
	 /* Already enabled */
	 break;
	 
      case WANTNO:
	 switch(usq[option])
	 {
	 case EMPTY:
	    /* Already negotiating for YES, queue the request */
	    usq[option] = OPPOSITE;
	    break;
	 case OPPOSITE:
	    /* Error: already queued an enable request */
	    break;
	 }
	 break;
	 
      case WANTYES:
	 switch(usq[option])
	 {
	 case EMPTY:
	    /* Error: already negotiating for enable */
	    break;
	 case OPPOSITE:
	    usq[option] = EMPTY;
	    break;
	 }
	 break;
      }
   }
   else /* NO */
   {
      switch(us[option])
      {
      case NO:
	 /* Already disabled */
	 break;
	 
      case YES:
	 us[option] = WANTNO;
	 send_negotiation(data, WONT, option);
	 break;
	 
      case WANTNO:
	 switch(usq[option])
	 {
	 case EMPTY:
	    /* Already negotiating for NO */
	    break;
	 case OPPOSITE:
	    usq[option] = EMPTY;
	    break;
	 }
	 break;
	 
      case WANTYES:
	 switch(usq[option])
	 {
	 case EMPTY:
	    usq[option] = OPPOSITE;
	    break;
	 case OPPOSITE:
	    break;
	 }
	 break;
      }
   }
}