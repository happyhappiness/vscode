{
    /* We have a password in the URL so decode it */
    char *newpasswd;
    result = Curl_urldecode(data, passwdp, 0, &newpasswd, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*passwd);
    *passwd = newpasswd;
  }