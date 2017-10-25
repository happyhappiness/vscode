void telrcv(struct UrlData *data,
	    unsigned char *inbuf,	/* Data received from socket */
	    int count)			/* Number of bytes received */
{
   unsigned char c;
   int index = 0;

   while(count--)
   {
      c = inbuf[index++];

      switch (telrcv_state)
      {
      case TS_CR:
	 telrcv_state = TS_DATA;
	 if (c == '\0')
	 {
	    break;   /* Ignore \0 after CR */
	 }
	 
	 data->fwrite((char *)&c, 1, 1, data->out);
	 continue;

      case TS_DATA:
	 if (c == IAC)
	 {
	    telrcv_state = TS_IAC;
	    break;
	 }
	 else if(c == '\r')
	 {
	    telrcv_state = TS_CR;
	 }

	 data->fwrite((char *)&c, 1, 1, data->out);
	 continue;

      case TS_IAC:
	process_iac:
	switch (c)
	{
	case WILL:
	   telrcv_state = TS_WILL;
	   continue;
	case WONT:
	   telrcv_state = TS_WONT;
	   continue;
	case DO:
	   telrcv_state = TS_DO;
	   continue;
	case DONT:
	   telrcv_state = TS_DONT;
	   continue;
	case SB:
	   SB_CLEAR();
	   telrcv_state = TS_SB;
	   continue;
	case IAC:
	   data->fwrite((char *)&c, 1, 1, data->out);
	   break;
	case DM:
	case NOP:
	case GA:
	default:
	   printoption(data, "RCVD", IAC, c);
	   break;
	}
	telrcv_state = TS_DATA;
	continue;

      case TS_WILL:
	 printoption(data, "RCVD", WILL, c);
	 rec_will(data, c);
	 telrcv_state = TS_DATA;
	 continue;
      
      case TS_WONT:
	 printoption(data, "RCVD", WONT, c);
	 rec_wont(data, c);
	 telrcv_state = TS_DATA;
	 continue;
      
      case TS_DO:
	 printoption(data, "RCVD", DO, c);
	 rec_do(data, c);
	 telrcv_state = TS_DATA;
	 continue;
      
      case TS_DONT:
	 printoption(data, "RCVD", DONT, c);
	 rec_dont(data, c);
	 telrcv_state = TS_DATA;
	 continue;

      case TS_SB:
	 if (c == IAC)
	 {
	    telrcv_state = TS_SE;
	 }
	 else
	 {
	    SB_ACCUM(c);
	 }
	 continue;

      case TS_SE:
	 if (c != SE)
	 {
	    if (c != IAC)
	    {
	       /*
		* This is an error.  We only expect to get
		* "IAC IAC" or "IAC SE".  Several things may
		* have happend.  An IAC was not doubled, the
		* IAC SE was left off, or another option got
		* inserted into the suboption are all possibilities.
		* If we assume that the IAC was not doubled,
		* and really the IAC SE was left off, we could
		* get into an infinate loop here.  So, instead,
		* we terminate the suboption, and process the
		* partial suboption if we can.
		*/
	       SB_ACCUM((unsigned char)IAC);
	       SB_ACCUM(c);
	       subpointer -= 2;
	       SB_TERM();
	    
	       printoption(data, "In SUBOPTION processing, RCVD", IAC, c);
	       suboption(data);   /* handle sub-option */
	       telrcv_state = TS_IAC;
	       goto process_iac;
	    }
	    SB_ACCUM(c);
	    telrcv_state = TS_SB;
	 }
	 else
	 {
	    SB_ACCUM((unsigned char)IAC);
	    SB_ACCUM((unsigned char)SE);
	    subpointer -= 2;
	    SB_TERM();
	    suboption(data);   /* handle sub-option */
	    telrcv_state = TS_DATA;
	 }
	 break;
      }
   }
}