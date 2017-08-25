{
          /***
           *DANG* this is an RFC 2068 violation. The URL is supposed
           to be absolute and this doesn't seem to be that!
           ***
           Instead, we have to TRY to append this new path to the old URL
           to the right of the host part. Oh crap, this is doomed to cause
           problems in the future...
          */
          char *protsep;
          char *pathsep;
          char *newest;

          /* we must make our own copy of the URL to play with, as it may
             point to read-only data */
          char *url_clone=strdup(data->change.url);

          if(!url_clone) {
            res = CURLE_OUT_OF_MEMORY;
            break; /* skip out of this loop NOW */
          }

          /* protsep points to the start of the host name */
          protsep=strstr(url_clone, "//");
          if(!protsep)
            protsep=url_clone;
          else
            protsep+=2; /* pass the slashes */

          if('/' != newurl[0]) {
            /* First we need to find out if there's a ?-letter in the URL,
               and cut it and the right-side of that off */
            pathsep = strrchr(protsep, '?');
            if(pathsep)
              *pathsep=0;

            /* we have a relative path to append to the last slash if
               there's one available */
            pathsep = strrchr(protsep, '/');
            if(pathsep)
              *pathsep=0;
          }
          else {
            /* We got a new absolute path for this server, cut off from the
               first slash */
            pathsep = strchr(protsep, '/');
            if(pathsep)
              *pathsep=0;
          }

          newest=(char *)malloc( strlen(url_clone) +
                                 1 + /* possible slash */
                                 strlen(newurl) + 1/* zero byte */);

          if(!newest) {
            res = CURLE_OUT_OF_MEMORY;
            break; /* go go go out from this loop */
          }
          sprintf(newest, "%s%s%s", url_clone, ('/' == newurl[0])?"":"/",
                  newurl);
          free(newurl);
          free(url_clone);
          newurl = newest;
        }