f((url_has_scheme && strncasecompare(data->change.url, "file:", 5)) ||
     (!url_has_scheme && data->set.str[STRING_DEFAULT_PROTOCOL] &&
      strcasecompare(data->set.str[STRING_DEFAULT_PROTOCOL], "file"))) {
    bool path_has_drive = FALSE;

    if(url_has_scheme)
      rc = sscanf(data->change.url, "%*15[^\n/:]:%[^\n]", path);
    else
      rc = sscanf(data->change.url, "%[^\n]", path);

    if(rc != 1) {
      failf(data, "Bad URL");
      return CURLE_URL_MALFORMAT;
    }

    if(url_has_scheme && path[0] == '/' && path[1] == '/') {
      /* Allow omitted hostname (e.g. file:/<path>).  This is not strictly
       * speaking a valid file: URL by RFC 1738, but treating file:/<path> as
       * file://localhost/<path> is similar to how other schemes treat missing
       * hostnames.  See RFC 1808. */

      /* This cannot be done with strcpy() in a portable manner, since the
         memory areas overlap! */
      memmove(path, path + 2, strlen(path + 2)+1);
    }

    /* the path may start with a drive letter. for backwards compatibility
       we skip some processing on those paths. */
    path_has_drive = (('a' <= path[0] && path[0] <= 'z') ||
                      ('A' <= path[0] && path[0] <= 'Z')) && path[1] == ':';

    /*
     * we deal with file://<host>/<path> differently since it supports no
     * hostname other than "localhost" and "127.0.0.1", which is unique among
     * the URL protocols specified in RFC 1738
     */
    if(path[0] != '/' && !path_has_drive) {
      /* the URL includes a host name, it must match "localhost" or
         "127.0.0.1" to be valid */
      char *ptr;
      if(!checkprefix("localhost/", path) &&
         !checkprefix("127.0.0.1/", path)) {
        failf(data, "Invalid file://hostname/, "
                    "expected localhost or 127.0.0.1 or none");
        return CURLE_URL_MALFORMAT;
      }
      ptr = &path[9]; /* now points to the slash after the host */

      /* there was a host name and slash present

         RFC1738 (section 3.1, page 5) says:

         The rest of the locator consists of data specific to the scheme,
         and is known as the "url-path". It supplies the details of how the
         specified resource can be accessed. Note that the "/" between the
         host (or port) and the url-path is NOT part of the url-path.

         As most agents use file://localhost/foo to get '/foo' although the
         slash preceding foo is a separator and not a slash for the path,
         a URL as file://localhost//foo must be valid as well, to refer to
         the same file with an absolute path.
      */

      if('/' == ptr[1])
        /* if there was two slashes, we skip the first one as that is then
           used truly as a separator */
        ptr++;

      /* This cannot be made with strcpy, as the memory chunks overlap! */
      memmove(path, ptr, strlen(ptr)+1);

      path_has_drive = (('a' <= path[0] && path[0] <= 'z') ||
                        ('A' <= path[0] && path[0] <= 'Z')) && path[1] == ':';
    }

#if !defined(MSDOS) && !defined(WIN32) && !defined(__CYGWIN__)
    if(path_has_drive) {
      failf(data, "File drive letters are only accepted in MSDOS/Windows.");
      return CURLE_URL_MALFORMAT;
    }
#endif

    protop = "file"; /* protocol string */
    *prot_missing = !url_has_scheme;
  }
  else {
    /* clear path */
    char slashbuf[4];
    path[0]=0;

    rc = sscanf(data->change.url,
                "%15[^\n/:]:%3[/]%[^\n/?#]%[^\n]",
                protobuf, slashbuf, conn->host.name, path);
    if(2 == rc) {
      failf(data, "Bad URL");
      return CURLE_URL_MALFORMAT;
    }
    if(3 > rc) {

      /*
       * The URL was badly formatted, let's try the browser-style _without_
       * protocol specified like 'http://'.
       */
      rc = sscanf(data->change.url, "%[^\n/?#]%[^\n]", conn->host.name, path);
      if(1 > rc) {
        /*
         * We couldn't even get this format.
         * djgpp 2.04 has a sscanf() bug where 'conn->host.name' is
         * assigned, but the return value is EOF!
         */
#if defined(__DJGPP__) && (DJGPP_MINOR == 4)
        if(!(rc == -1 && *conn->host.name))
#endif
        {
          failf(data, "<url> malformed");
          return CURLE_URL_MALFORMAT;
        }
      }

      /*
       * Since there was no protocol part specified in the URL use the
       * user-specified default protocol. If we weren't given a default make a
       * guess by matching some protocols against the host's outermost
       * sub-domain name. Finally if there was no match use HTTP.
       */

      protop = data->set.str[STRING_DEFAULT_PROTOCOL];
      if(!protop) {
        /* Note: if you add a new protocol, please update the list in
         * lib/version.c too! */
        if(checkprefix("FTP.", conn->host.name))
          protop = "ftp";
        else if(checkprefix("DICT.", conn->host.name))
          protop = "DICT";
        else if(checkprefix("LDAP.", conn->host.name))
          protop = "LDAP";
        else if(checkprefix("IMAP.", conn->host.name))
          protop = "IMAP";
        else if(checkprefix("SMTP.", conn->host.name))
          protop = "smtp";
        else if(checkprefix("POP3.", conn->host.name))
          protop = "pop3";
        else
          protop = "http";
      }

      *prot_missing = TRUE; /* not given in URL */
    }
    else {
      size_t s = strlen(slashbuf);
      protop = protobuf;
      if(s != 2) {
        infof(data, "Unwillingly accepted illegal URL using %d slash%s!\n",
              s, s>1?"es":"");

        if(data->change.url_alloc)
          free(data->change.url);
        /* repair the URL to use two slashes */
        data->change.url = aprintf("%s://%s%s",
                                   protobuf, conn->host.name, path);
        if(!data->change.url)
          return CURLE_OUT_OF_MEMORY;
        data->change.url_alloc = TRUE;
      }
    }
  }