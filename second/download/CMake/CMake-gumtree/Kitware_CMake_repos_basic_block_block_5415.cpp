f(data->set.str[STRING_MAIL_AUTH][0] != '\0')
      auth = aprintf("%s", data->set.str[STRING_MAIL_AUTH]);
    else
      /* Empty AUTH, RFC-2554, sect. 5 */
      auth = strdup("<>")