static
void telrcv(struct connectdata *conn,
            unsigned char *inbuf,	/* Data received from socket */
            int count)			/* Number of bytes received */
{
  unsigned char c;
  int index = 0;
  struct SessionHandle *data = conn->data;
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;

  while(count--)
  {
    c = inbuf[index++];

    switch (tn->telrcv_state)
    {
      case TS_CR:
        tn->telrcv_state = TS_DATA;
        if (c == '\0')
        {
          break;   /* Ignore \0 after CR */
        }

        Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
        continue;

      case TS_DATA:
        if (c == IAC)
        {
          tn->telrcv_state = TS_IAC;
          break;
        }
        else if(c == '\r')
        {
          tn->telrcv_state = TS_CR;
        }

        Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
        continue;

      case TS_IAC:
      process_iac:
      switch (c)
      {
        case WILL:
          tn->telrcv_state = TS_WILL;
          continue;
        case WONT:
          tn->telrcv_state = TS_WONT;
          continue;
        case DO:
          tn->telrcv_state = TS_DO;
          continue;
        case DONT:
          tn->telrcv_state = TS_DONT;
          continue;
        case SB:
          SB_CLEAR(tn);
          tn->telrcv_state = TS_SB;
          continue;
        case IAC:
          Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
          break;
        case DM:
        case NOP:
        case GA:
        default:
          printoption(data, "RCVD", IAC, c);
          break;
      }
      tn->telrcv_state = TS_DATA;
      continue;

      case TS_WILL:
        printoption(data, "RCVD", WILL, c);
        tn->please_negotiate = 1;
        rec_will(conn, c);
        tn->telrcv_state = TS_DATA;
        continue;
      
      case TS_WONT:
        printoption(data, "RCVD", WONT, c);
        tn->please_negotiate = 1;
        rec_wont(conn, c);
        tn->telrcv_state = TS_DATA;
        continue;
      
      case TS_DO:
        printoption(data, "RCVD", DO, c);
        tn->please_negotiate = 1;
        rec_do(conn, c);
        tn->telrcv_state = TS_DATA;
        continue;
      
      case TS_DONT:
        printoption(data, "RCVD", DONT, c);
        tn->please_negotiate = 1;
        rec_dont(conn, c);
        tn->telrcv_state = TS_DATA;
        continue;

      case TS_SB:
        if (c == IAC)
        {
          tn->telrcv_state = TS_SE;
        }
        else
        {
          SB_ACCUM(tn,c);
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
            SB_ACCUM(tn, (unsigned char)IAC);
            SB_ACCUM(tn, c);
            tn->subpointer -= 2;
            SB_TERM(tn);
	    
            printoption(data, "In SUBOPTION processing, RCVD", IAC, c);
            suboption(conn);   /* handle sub-option */
            tn->telrcv_state = TS_IAC;
            goto process_iac;
          }
          SB_ACCUM(tn,c);
          tn->telrcv_state = TS_SB;
        }
        else
        {
          SB_ACCUM(tn, (unsigned char)IAC);
          SB_ACCUM(tn, (unsigned char)SE);
          tn->subpointer -= 2;
          SB_TERM(tn);
          suboption(conn);   /* handle sub-option */
          tn->telrcv_state = TS_DATA;
        }
        break;
    }
  }
}