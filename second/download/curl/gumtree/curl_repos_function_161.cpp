void rec_do(struct UrlData *data, int option)
{
   switch(us[option])
   {
   case NO:
      if(us_preferred[option] == YES)
      {
	 us[option] = YES;
	 send_negotiation(data, WILL, option);
      }
      else
      {
	 send_negotiation(data, WONT, option);
      }
      break;
	 
   case YES:
      /* Already enabled */
      break;
	 
   case WANTNO:
      switch(usq[option])
      {
      case EMPTY:
	 /* Error: DONT answered by WILL */
	 us[option] = NO;
	 break;
      case OPPOSITE:
	 /* Error: DONT answered by WILL */
	 us[option] = YES;
	 usq[option] = EMPTY;
	 break;
      }
      break;
	 
   case WANTYES:
      switch(usq[option])
      {
      case EMPTY:
	 us[option] = YES;
	 break;
      case OPPOSITE:
	 us[option] = WANTNO;
	 himq[option] = EMPTY;
	 send_negotiation(data, WONT, option);
	 break;
      }
      break;
   }
}