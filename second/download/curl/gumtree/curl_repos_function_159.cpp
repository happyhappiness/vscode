void rec_wont(struct UrlData *data, int option)
{
   switch(him[option])
   {
   case NO:
      /* Already disabled */
      break;
	 
   case YES:
      him[option] = NO;
      send_negotiation(data, DONT, option);
      break;
	 
   case WANTNO:
      switch(himq[option])
      {
      case EMPTY:
	 him[option] = NO;
	 break;
	 
      case OPPOSITE:
	 him[option] = WANTYES;
	 himq[option] = EMPTY;
	 send_negotiation(data, DO, option);
	 break;
      }
      break;
	 
   case WANTYES:
      switch(himq[option])
      {
      case EMPTY:
	 him[option] = NO;
	 break;
      case OPPOSITE:
	 him[option] = NO;
	 himq[option] = EMPTY;
	 break;
      }
      break;
   }
}