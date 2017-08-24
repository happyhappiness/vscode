{
    char *newname;

    /* We have a user in the URL */
    conn->bits.userpwd_in_url = TRUE;
    conn->bits.user_passwd = TRUE; /* enable user+password */

    /* Decode the user */
    result = Curl_urldecode(data, userp, 0, &newname, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*user);
    *user = newname;
  }