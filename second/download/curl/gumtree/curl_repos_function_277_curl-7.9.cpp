static int check_telnet_options(struct connectdata *conn)
{
  struct curl_slist *head;
  char option_keyword[128];
  char option_arg[256];
  char *buf;
  struct SessionHandle *data = conn->data;
  struct TELNET *tn = (struct TELNET *)conn->proto.telnet;

  /* Add the user name as an environment variable if it
     was given on the command line */
  if(conn->bits.user_passwd)
  {
    char *buf = malloc(256);
    sprintf(buf, "USER,%s", data->state.user);
    tn->telnet_vars = curl_slist_append(tn->telnet_vars, buf);

    tn->us_preferred[TELOPT_NEW_ENVIRON] = YES;
  }

  for(head = data->set.telnet_options; head; head=head->next) {
    if(sscanf(head->data, "%127[^= ]%*[ =]%255s",
              option_keyword, option_arg) == 2) {

      /* Terminal type */
      if(strequal(option_keyword, "TTYPE")) {
        strncpy(tn->subopt_ttype, option_arg, 31);
        tn->subopt_ttype[31] = 0; /* String termination */
        tn->us_preferred[TELOPT_TTYPE] = YES;
        continue;
      }

      /* Display variable */
      if(strequal(option_keyword, "XDISPLOC")) {
        strncpy(tn->subopt_xdisploc, option_arg, 127);
        tn->subopt_xdisploc[127] = 0; /* String termination */
        tn->us_preferred[TELOPT_XDISPLOC] = YES;
        continue;
      }

      /* Environment variable */
      if(strequal(option_keyword, "NEW_ENV")) {
        buf = strdup(option_arg);
        if(!buf)
          return CURLE_OUT_OF_MEMORY;
        tn->telnet_vars = curl_slist_append(tn->telnet_vars, buf);
        tn->us_preferred[TELOPT_NEW_ENVIRON] = YES;
        continue;
      }

      failf(data, "Unknown telnet option %s", head->data);
      return CURLE_UNKNOWN_TELNET_OPTION;
    } else {
      failf(data, "Syntax error in telnet option: %s", head->data);
      return CURLE_TELNET_OPTION_SYNTAX;
    }
  }

  return CURLE_OK;
}