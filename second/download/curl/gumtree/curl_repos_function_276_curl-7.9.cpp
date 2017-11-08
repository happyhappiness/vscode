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
      printf("%s IAC SB ", (direction == '<')? "RCVD":"SENT");
      if (length >= 3)
      {
        int j;

        i = pointer[length-2];
        j = pointer[length-1];

        if (i != IAC || j != SE)
        {
          printf("(terminated by ");
          if (TELOPT_OK(i))
            printf("%s ", TELOPT(i));
          else if (TELCMD_OK(i))
            printf("%s ", TELCMD(i));
          else
            printf("%d ", i);
          if (TELOPT_OK(j))
            printf("%s", TELOPT(j));
          else if (TELCMD_OK(j))
            printf("%s", TELCMD(j));
          else
            printf("%d", j);
          printf(", not IAC SE!) ");
        }
      }
      length -= 2;
    }
    if (length < 1)
    {
      printf("(Empty suboption?)");
      return;
    }

    if (TELOPT_OK(pointer[0])) {
      switch(pointer[0]) {
        case TELOPT_TTYPE:
        case TELOPT_XDISPLOC:
        case TELOPT_NEW_ENVIRON:
          printf("%s", TELOPT(pointer[0]));
          break;
        default:
          printf("%s (unsupported)", TELOPT(pointer[0]));
          break;
      }
    }
    else
      printf("%d (unknown)", pointer[i]);

    switch(pointer[1]) {
      case TELQUAL_IS:
        printf(" IS");
        break;
      case TELQUAL_SEND:
        printf(" SEND");
        break;
      case TELQUAL_INFO:
        printf(" INFO/REPLY");
        break;
      case TELQUAL_NAME:
        printf(" NAME");
        break;
    }
      
    switch(pointer[0]) {
      case TELOPT_TTYPE:
      case TELOPT_XDISPLOC:
        pointer[length] = 0;
        printf(" \"%s\"", &pointer[2]);
        break;
      case TELOPT_NEW_ENVIRON:
        if(pointer[1] == TELQUAL_IS) {
          printf(" ");
          for(i = 3;i < length;i++) {
            switch(pointer[i]) {
              case NEW_ENV_VAR:
                printf(", ");
                break;
              case NEW_ENV_VALUE:
                printf(" = ");
                break;
              default:
                printf("%c", pointer[i]);
                break;
            }
          }
        }
        break;
      default:
        for (i = 2; i < length; i++)
          printf(" %.2x", pointer[i]);
        break;
    }
      
    if (direction)
    {
      printf("\n");
    }
  }
}