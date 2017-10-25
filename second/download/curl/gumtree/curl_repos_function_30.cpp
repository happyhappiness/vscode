CURLcode curl_transfer(CURL *curl)
{
  CURLcode res;
  struct UrlData *data = curl;
  struct connectdata *c_connect;

  pgrsStartNow(data);

  do {
    res = curl_connect(curl, (CURLconnect **)&c_connect);
    if(res == CURLE_OK) {
      res = curl_do(c_connect);
      if(res == CURLE_OK) {
        res = _Transfer(c_connect); /* now fetch that URL please */
        if(res == CURLE_OK)
          res = curl_done(c_connect);
      }

      if((res == CURLE_OK) && data->newurl) {
        /* Location: redirect */
        char prot[16];
        char path[URL_MAX_LENGTH];

        /* mark the next request as a followed location: */
        data->bits.this_is_a_follow = TRUE;

        if(data->bits.http_auto_referer) {
          /* We are asked to automatically set the previous URL as the
             referer when we get the next URL. We pick the ->url field,
             which may or may not be 100% correct */

          if(data->free_referer) {
            /* If we already have an allocated referer, free this first */
            free(data->referer);
          }

          data->referer = strdup(data->url);
          data->free_referer = TRUE; /* yes, free this later */
          data->bits.http_set_referer = TRUE; /* might have been false */
        }

        if(2 != sscanf(data->newurl, "%15[^:]://%" URL_MAX_LENGTH_TXT
                       "s", prot, path)) {
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

          /* protsep points to the start of the host name */
          protsep=strstr(data->url, "//");
          if(!protsep)
            protsep=data->url;
          else {
            /* TBD: set the port with curl_setopt() */
            data->port=0; /* we got a full URL and then we should reset the
                             port number here to re-initiate it later */
            protsep+=2; /* pass the slashes */
          }

          if('/' != data->newurl[0]) {
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

          newest=(char *)malloc( strlen(data->url) +
                                 1 + /* possible slash */
                                 strlen(data->newurl) + 1/* zero byte */);

          if(!newest)
            return CURLE_OUT_OF_MEMORY;
          sprintf(newest, "%s%s%s", data->url, ('/' == data->newurl[0])?"":"/",
                  data->newurl);
          free(data->newurl);
          data->newurl = newest;
        }
        else {
          /* This was an absolute URL, clear the port number! */
          /* TBD: set the port with curl_setopt() */
          data->port = 0;
        }
      
        /* TBD: set the URL with curl_setopt() */
        data->url = data->newurl;
        data->newurl = NULL; /* don't show! */

        /* Disable both types of POSTs, since doing a second POST when
           following isn't what anyone would want! */
        data->bits.http_post = FALSE;
        data->bits.http_formpost = FALSE;

        infof(data, "Follows Location: to new URL: '%s'\n", data->url);

        curl_disconnect(c_connect);
        continue;
      }

      curl_disconnect(c_connect);
    }
    break; /* it only reaches here when this shouldn't loop */

  } while(1); /* loop if Location: */

  if(data->newurl)
    free(data->newurl);

  if((CURLE_OK == res) && data->writeinfo) {
    /* Time to output some info to stdout */
    WriteOut(data);
  }
  return res;
}