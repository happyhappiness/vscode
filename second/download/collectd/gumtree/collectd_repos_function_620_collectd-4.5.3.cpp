static int authinteract (auth_client_request_t request, char **result,
    int fields, void *arg)
{               
  int i;
  for (i = 0; i < fields; i++)
  {
    if (request[i].flags & AUTH_USER)
      result[i] = smtp_user;
    else if (request[i].flags & AUTH_PASS)
      result[i] = smtp_password;
    else
      return 0;
  }
  return 1;
}