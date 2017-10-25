static
void telrcv(struct connectdata *conn,
            unsigned char *inbuf,       /* Data received from socket */
            ssize_t count)              /* Number of bytes received */
{
  unsigned char c;
  int in = 0;
  struct SessionHandle *data = conn->data;
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;

  while(count--)
  {
    c = inbuf[in++];

    switch (tn->telrcv_state)
    {
      case CURL_TS_CR:
        tn->telrcv_state = CURL_TS_DATA;
        if (c == '\0')
        {
          break;   /* Ignore \0 after CR */
        }

        Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
        continue;

      case CURL_TS_DATA:
        if (c == CURL_IAC)
        {
          tn->telrcv_state = CURL_TS_IAC;
          break;
        }
        else if(c == '\r')
        {
          tn->telrcv_state = CURL_TS_CR;
        }

        Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
        continue;

      case CURL_TS_IAC:
      process_iac:
      switch (c)
      {
        case CURL_WILL:
          tn->telrcv_state = CURL_TS_WILL;
          continue;
        case CURL_WONT:
          tn->telrcv_state = CURL_TS_WONT;
          continue;
        case CURL_DO:
          tn->telrcv_state = CURL_TS_DO;
          continue;
        case CURL_DONT:
          tn->telrcv_state = CURL_TS_DONT;
          continue;
        case CURL_SB:
          CURL_SB_CLEAR(tn);
          tn->telrcv_state = CURL_TS_SB;
          continue;
        case CURL_IAC:
          Curl_client_write(data, CLIENTWRITE_BODY, (char *)&c, 1);
          break;
        case CURL_DM:
        case CURL_NOP:
        case CURL_GA:
        default:
          printoption(data, "RCVD", CURL_IAC, c);
          break;
      }
      tn->telrcv_state = CURL_TS_DATA;
      continue;

      case CURL_TS_WILL:
        printoption(data, "RCVD", CURL_WILL, c);
        tn->please_negotiate = 1;
        rec_will(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        continue;

      case CURL_TS_WONT:
        printoption(data, "RCVD", CURL_WONT, c);
        tn->please_negotiate = 1;
        rec_wont(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        continue;

      case CURL_TS_DO:
        printoption(data, "RCVD", CURL_DO, c);
        tn->please_negotiate = 1;
        rec_do(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        continue;

      case CURL_TS_DONT:
        printoption(data, "RCVD", CURL_DONT, c);
        tn->please_negotiate = 1;
        rec_dont(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        continue;

      case CURL_TS_SB:
        if (c == CURL_IAC)
        {
          tn->telrcv_state = CURL_TS_SE;
        }
        else
        {
          CURL_SB_ACCUM(tn,c);
        }
        continue;

      case CURL_TS_SE:
        if (c != CURL_SE)
        {
          if (c != CURL_IAC)
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
            CURL_SB_ACCUM(tn, (unsigned char)CURL_IAC);
            CURL_SB_ACCUM(tn, c);
            tn->subpointer -= 2;
            CURL_SB_TERM(tn);

            printoption(data, "In SUBOPTION processing, RCVD", CURL_IAC, c);
            suboption(conn);   /* handle sub-option */
            tn->telrcv_state = CURL_TS_IAC;
            goto process_iac;
          }
          CURL_SB_ACCUM(tn,c);
          tn->telrcv_state = CURL_TS_SB;
        }
        else
        {
          CURL_SB_ACCUM(tn, (unsigned char)CURL_IAC);
          CURL_SB_ACCUM(tn, (unsigned char)CURL_SE);
          tn->subpointer -= 2;
          CURL_SB_TERM(tn);
          suboption(conn);   /* handle sub-option */
          tn->telrcv_state = CURL_TS_DATA;
        }
        break;
    }
  }
}