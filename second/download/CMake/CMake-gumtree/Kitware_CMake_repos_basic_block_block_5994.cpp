{
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