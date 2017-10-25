void rec_dont(struct UrlData *data, int option)
{
   switch(us[option])
   {
   case NO:
      /* Already disabled */
      break;
	 
   case YES:
      us[option] = NO;
      send_negotiation(data, WONT, option);
      break;
	 
   case WANTNO:
      switch(usq[option])
      {
      case EMPTY:
	 us[option] = NO;
	 break;
	 
      case OPPOSITE:
	 us[option] = WANTYES;
	 usq[option] = EMPTY;
	 send_negotiation(data, WILL, option);
	 break;
      }
      break;
	 
   case WANTYES:
      switch(usq[option])
      {
      case EMPTY:
	 us[option] = NO;
	 break;
      case OPPOSITE:
	 us[option] = NO;
	 usq[option] = EMPTY;
	 break;
      }
      break;
   }
}