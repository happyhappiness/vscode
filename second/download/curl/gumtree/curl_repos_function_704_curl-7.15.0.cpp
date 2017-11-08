static
void rec_will(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;
  switch(tn->him[option])
  {
    case CURL_NO:
      if(tn->him_preferred[option] == CURL_YES)
      {
        tn->him[option] = CURL_YES;
        send_negotiation(conn, CURL_DO, option);
      }
      else
      {
        send_negotiation(conn, CURL_DONT, option);
      }
      break;

    case CURL_YES:
      /* Already enabled */
      break;

    case CURL_WANTNO:
      switch(tn->himq[option])
      {
        case CURL_EMPTY:
          /* Error: DONT answered by WILL */
          tn->him[option] = CURL_NO;
          break;
        case CURL_OPPOSITE:
          /* Error: DONT answered by WILL */
          tn->him[option] = CURL_YES;
          tn->himq[option] = CURL_EMPTY;
          break;
      }
      break;

    case CURL_WANTYES:
      switch(tn->himq[option])
      {
        case CURL_EMPTY:
          tn->him[option] = CURL_YES;
          break;
        case CURL_OPPOSITE:
          tn->him[option] = CURL_WANTNO;
          tn->himq[option] = CURL_EMPTY;
          send_negotiation(conn, CURL_DONT, option);
          break;
      }
      break;
  }
}