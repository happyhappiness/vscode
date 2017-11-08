static
void rec_do(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->us[option])
  {
    case CURL_NO:
      if(tn->us_preferred[option] == CURL_YES)
      {
        tn->us[option] = CURL_YES;
        send_negotiation(conn, CURL_WILL, option);
      }
      else
      {
        send_negotiation(conn, CURL_WONT, option);
      }
      break;

    case CURL_YES:
      /* Already enabled */
      break;

    case CURL_WANTNO:
      switch(tn->usq[option])
      {
        case CURL_EMPTY:
          /* Error: DONT answered by WILL */
          tn->us[option] = CURL_NO;
          break;
        case CURL_OPPOSITE:
          /* Error: DONT answered by WILL */
          tn->us[option] = CURL_YES;
          tn->usq[option] = CURL_EMPTY;
          break;
      }
      break;

    case CURL_WANTYES:
      switch(tn->usq[option])
      {
        case CURL_EMPTY:
          tn->us[option] = CURL_YES;
          break;
        case CURL_OPPOSITE:
          tn->us[option] = CURL_WANTNO;
          tn->himq[option] = CURL_EMPTY;
          send_negotiation(conn, CURL_WONT, option);
          break;
      }
      break;
  }
}