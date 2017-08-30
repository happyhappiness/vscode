       */

      if((res == CURLE_OK) && newurl) {
        /* Location: redirect
 
           This is assumed to happen for HTTP(S) only!
        */
        char prot[16]; /* URL protocol string storage */
        char letter;   /* used for a silly sscanf */

        if (data->set.maxredirs && (data->set.followlocation >= data->set.maxredirs)) {
          failf(data,"Maximum (%d) redirects followed", data->set.maxredirs);
          res=CURLE_TOO_MANY_REDIRECTS;
          break;
        }

        /* mark the next request as a followed location: */
        data->state.this_is_a_follow = TRUE;

        data->set.followlocation++; /* count location-followers */

        if(data->set.http_auto_referer) {
          /* We are asked to automatically set the previous URL as the
             referer when we get the next URL. We pick the ->url field,
             which may or may not be 100% correct */

          if(data->change.referer_alloc)
            /* If we already have an allocated referer, free this first */
            free(data->change.referer);

          data->change.referer = strdup(data->change.url);
          data->change.referer_alloc = TRUE; /* yes, free this later */
        }

        if(2 != sscanf(newurl, "%15[^?&/:]://%c", prot, &letter)) {
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
        else
          /* This is an absolute URL, don't allow the custom port number */
          data->state.allow_port = FALSE;

        if(data->change.url_alloc)
          free(data->change.url);
        else
          data->change.url_alloc = TRUE; /* the URL is allocated */
      
        /* TBD: set the URL with curl_setopt() */
        data->change.url = newurl;
        newurl = NULL; /* don't free! */

        infof(data, "Follows Location: to new URL: '%s'\n", data->change.url);

        /*
         * We get here when the HTTP code is 300-399. We need to perform
         * differently based on exactly what return code there was.
         * Discussed on the curl mailing list and posted about on the 26th
         * of January 2001.
         */
        switch(data->info.httpcode) {
        case 300: /* Multiple Choices */
        case 301: /* Moved Permanently */
        case 306: /* Not used */
        case 307: /* Temporary Redirect */
        default:  /* for all unknown ones */
          /* These are explicitly mention since I've checked RFC2616 and they
           * seem to be OK to POST to.
           */
          break;
        case 302: /* Found */
          /* (From 10.3.3)

            Note: RFC 1945 and RFC 2068 specify that the client is not allowed
            to change the method on the redirected request.  However, most
            existing user agent implementations treat 302 as if it were a 303
            response, performing a GET on the Location field-value regardless
            of the original request method. The status codes 303 and 307 have
            been added for servers that wish to make unambiguously clear which
            kind of reaction is expected of the client.

            (From 10.3.4)

            Note: Many pre-HTTP/1.1 user agents do not understand the 303
            status. When interoperability with such clients is a concern, the
            302 status code may be used instead, since most user agents react
            to a 302 response as described here for 303.             
          */
        case 303: /* See Other */
          /* Disable both types of POSTs, since doing a second POST when
           * following isn't what anyone would want! */
          data->set.httpreq = HTTPREQ_GET; /* enforce GET request */
          infof(data, "Disables POST, goes with GET\n");
          break;
        case 304: /* Not Modified */
          /* 304 means we did a conditional request and it was "Not modified".
           * We shouldn't get any Location: header in this response!
           */
          break;
        case 305: /* Use Proxy */
          /* (quote from RFC2616, section 10.3.6):
           * "The requested resource MUST be accessed through the proxy given
           * by the Location field. The Location field gives the URI of the
           * proxy.  The recipient is expected to repeat this single request
           * via the proxy. 305 responses MUST only be generated by origin
           * servers."
           */
          break;
        }
        continue;
      }
    }
    break; /* it only reaches here when this shouldn't loop */
