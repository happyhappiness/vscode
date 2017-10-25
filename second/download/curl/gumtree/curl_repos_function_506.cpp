CURLcode Curl_dict(struct connectdata *conn, bool *done)
{
  char *word;
  char *ppath;
  char *database = NULL;
  char *strategy = NULL;
  char *nthdef = NULL; /* This is not part of the protocol, but required
                          by RFC 2229 */
  CURLcode result=CURLE_OK;
  struct SessionHandle *data=conn->data;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];

  char *path = conn->path;
  curl_off_t *bytecount = &conn->bytecount;

  *done = TRUE; /* unconditionally */

  if(conn->bits.user_passwd) {
    /* AUTH is missing */
  }

  if (strnequal(path, DICT_MATCH, sizeof(DICT_MATCH)-1) ||
      strnequal(path, DICT_MATCH2, sizeof(DICT_MATCH2)-1) ||
      strnequal(path, DICT_MATCH3, sizeof(DICT_MATCH3)-1)) {

    word = strchr(path, ':');
    if (word) {
      word++;
      database = strchr(word, ':');
      if (database) {
        *database++ = (char)0;
        strategy = strchr(database, ':');
        if (strategy) {
          *strategy++ = (char)0;
          nthdef = strchr(strategy, ':');
          if (nthdef) {
            *nthdef++ = (char)0;
          }
        }
      }
    }

    if ((word == NULL) || (*word == (char)0)) {
      failf(data, "lookup word is missing");
    }
    if ((database == NULL) || (*database == (char)0)) {
      database = (char *)"!";
    }
    if ((strategy == NULL) || (*strategy == (char)0)) {
      strategy = (char *)".";
    }

    result = Curl_sendf(sockfd, conn,
                        "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n"
                        "MATCH "
                        "%s "    /* database */
                        "%s "    /* strategy */
                        "%s\r\n" /* word */
                        "QUIT\r\n",

                        database,
                        strategy,
                        word
                        );
    if(result)
      failf(data, "Failed sending DICT request");
    else
      result = Curl_Transfer(conn, FIRSTSOCKET, -1, FALSE, bytecount,
                             -1, NULL); /* no upload */
    if(result)
      return result;
  }
  else if (strnequal(path, DICT_DEFINE, sizeof(DICT_DEFINE)-1) ||
           strnequal(path, DICT_DEFINE2, sizeof(DICT_DEFINE2)-1) ||
           strnequal(path, DICT_DEFINE3, sizeof(DICT_DEFINE3)-1)) {

    word = strchr(path, ':');
    if (word) {
      word++;
      database = strchr(word, ':');
      if (database) {
        *database++ = (char)0;
        nthdef = strchr(database, ':');
        if (nthdef) {
          *nthdef++ = (char)0;
        }
      }
    }

    if ((word == NULL) || (*word == (char)0)) {
      failf(data, "lookup word is missing");
    }
    if ((database == NULL) || (*database == (char)0)) {
      database = (char *)"!";
    }

    result = Curl_sendf(sockfd, conn,
                        "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n"
                        "DEFINE "
                        "%s "     /* database */
                        "%s\r\n"  /* word */
                        "QUIT\r\n",
                        database,
                        word);
    if(result)
      failf(data, "Failed sending DICT request");
    else
      result = Curl_Transfer(conn, FIRSTSOCKET, -1, FALSE, bytecount,
                             -1, NULL); /* no upload */

    if(result)
      return result;

  }
  else {

    ppath = strchr(path, '/');
    if (ppath) {
      int i;

      ppath++;
      for (i = 0; ppath[i]; i++) {
        if (ppath[i] == ':')
          ppath[i] = ' ';
      }
      result = Curl_sendf(sockfd, conn,
                          "CLIENT " LIBCURL_NAME " " LIBCURL_VERSION "\r\n"
                          "%s\r\n"
                          "QUIT\r\n", ppath);
      if(result)
        failf(data, "Failed sending DICT request");
      else
        result = Curl_Transfer(conn, FIRSTSOCKET, -1, FALSE, bytecount,
                               -1, NULL);
      if(result)
        return result;
    }
  }

  return CURLE_OK;
}