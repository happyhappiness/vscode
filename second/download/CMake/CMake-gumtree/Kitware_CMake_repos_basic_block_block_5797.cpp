{
    result = parse_login_details(option, strlen(option),
                                 (userp ? &user : NULL),
                                 (passwdp ? &passwd : NULL),
                                 NULL);
  }