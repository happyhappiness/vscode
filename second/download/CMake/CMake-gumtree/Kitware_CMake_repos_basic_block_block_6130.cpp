{
    /* Store the user, zero-length if not set */
    conn->user = strdup(user);

    /* Store the password (only if user is present), zero-length if not set */
    if(conn->user)
      conn->passwd = strdup(passwd);
    else
      conn->passwd = NULL;
  }