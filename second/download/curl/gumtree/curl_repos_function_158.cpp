void rec_will(struct UrlData *data, int option)
{
   switch(him[option])
   {
   case NO:
      if(him_preferred[option] == YES)
      {
	 him[option] = YES;
	 send_negotiation(data, DO, option);
      }
      else
      {
	 send_negotiation(data, DONT, option);
      }
      break;
	 
   case YES:
      /* Already enabled */
      break;
	 
   case WANTNO:
      switch(himq[option])
      {
      case EMPTY:
	 /* Error: DONT answered by WILL */
	 him[option] = NO;
	 break;
      case OPPOSITE:
	 /* Error: DONT answered by WILL */
	 him[option] = YES;
	 himq[option] = EMPTY;
	 break;
      }
      break;
	 
   case WANTYES:
      switch(himq[option])
      {
      case EMPTY:
	 him[option] = YES;
	 break;
      case OPPOSITE:
	 him[option] = WANTNO;
	 himq[option] = EMPTY;
	 send_negotiation(data, DONT, option);
	 break;
      }
      break;
   }
}