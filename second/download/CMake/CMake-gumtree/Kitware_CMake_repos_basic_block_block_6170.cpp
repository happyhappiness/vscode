{
    /* use the new user name and password though */
    Curl_safefree(conn->user);
    Curl_safefree(conn->passwd);
    conn->user = old_conn->user;
    conn->passwd = old_conn->passwd;
    old_conn->user = NULL;
    old_conn->passwd = NULL;
  }