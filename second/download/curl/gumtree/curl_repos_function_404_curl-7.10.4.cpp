static void printsub(struct SessionHandle *data,
		     int direction,		/* '<' or '>' */
		     unsigned char *pointer,	/* where suboption data is */
		     int length)		/* length of suboption data */
{
  int i = 0;

  if (data->set.verbose)
  {
    if (direction)
    {
      Curl_infof(data, "%s IAC SB ", (direction == '<')? "RCVD":"SENT");
      if (length >= 3)
      {
        int j;

        i = pointer[length-2];
        j = pointer[length-1];

        if (i != CURL_IAC || j != CURL_SE)
        {
          Curl_infof(data, "(terminated by ");
          if (CURL_TELOPT_OK(i))
            Curl_infof(data, "%s ", CURL_TELOPT(i));
          else if (CURL_TELCMD_OK(i))
            Curl_infof(data, "%s ", CURL_TELCMD(i));
          else
            Curl_infof(data, "%d ", i);
          if (CURL_TELOPT_OK(j))
            Curl_infof(data, "%s", CURL_TELOPT(j));
          else if (CURL_TELCMD_OK(j))
            Curl_infof(data, "%s", CURL_TELCMD(j));
          else
            Curl_infof(data, "%d", j);
          Curl_infof(data, ", not IAC SE!) ");
        }
      }
      length -= 2;
    }
    if (length < 1)
    {
      Curl_infof(data, "(Empty suboption?)");
      return;
    }

    if (CURL_TELOPT_OK(pointer[0])) {
      switch(pointer[0]) {
        case CURL_TELOPT_TTYPE:
        case CURL_TELOPT_XDISPLOC:
        case CURL_TELOPT_NEW_ENVIRON:
          Curl_infof(data, "%s", CURL_TELOPT(pointer[0]));
          break;
        default:
          Curl_infof(data, "%s (unsupported)", CURL_TELOPT(pointer[0]));
          break;
      }
    }
    else
      Curl_infof(data, "%d (unknown)", pointer[i]);

    switch(pointer[1]) {
      case CURL_TELQUAL_IS:
        Curl_infof(data, " IS");
        break;
      case CURL_TELQUAL_SEND:
        Curl_infof(data, " SEND");
        break;
      case CURL_TELQUAL_INFO:
        Curl_infof(data, " INFO/REPLY");
        break;
      case CURL_TELQUAL_NAME:
        Curl_infof(data, " NAME");
        break;
    }
      
    switch(pointer[0]) {
      case CURL_TELOPT_TTYPE:
      case CURL_TELOPT_XDISPLOC:
        pointer[length] = 0;
        Curl_infof(data, " \"%s\"", &pointer[2]);
        break;
      case CURL_TELOPT_NEW_ENVIRON:
        if(pointer[1] == CURL_TELQUAL_IS) {
          Curl_infof(data, " ");
          for(i = 3;i < length;i++) {
            switch(pointer[i]) {
              case CURL_NEW_ENV_VAR:
                Curl_infof(data, ", ");
                break;
              case CURL_NEW_ENV_VALUE:
                Curl_infof(data, " = ");
                break;
              default:
                Curl_infof(data, "%c", pointer[i]);
                break;
            }
          }
        }
        break;
      default:
        for (i = 2; i < length; i++)
          Curl_infof(data, " %.2x", pointer[i]);
        break;
    }
      
    if (direction)
    {
      Curl_infof(data, "\n");
    }
  }
}