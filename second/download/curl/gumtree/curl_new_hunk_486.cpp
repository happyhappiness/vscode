        config->resume_from = 0;
      }
      config->use_resume=TRUE;
      break;
    case 'd':
      /* postfield data */
    {
      char *postdata=NULL;
      FILE *file;

      if(subletter == 'e') { /* --data-urlencode*/
        /* [name]=[content], we encode the content part only
         * [name]@[file name]
         *
         * Case 2: we first load the file using that name and then encode
         * the content.
         */
        const char *p = strchr(nextarg, '=');
        size_t size = 0;
        size_t nlen;
        char is_file;
        if(!p)
          /* there was no '=' letter, check for a '@' instead */
          p = strchr(nextarg, '@');
        if(p) {
          nlen = p - nextarg; /* length of the name part */
          is_file = *p++; /* pass the separator */
        }
        else {
          /* neither @ nor =, so no name and it isn't a file */
          nlen = is_file = 0;
          p = nextarg;
        }
        if('@' == is_file) {
          /* a '@' letter, it means that a file name or - (stdin) follows */

          if(curlx_strequal("-", p)) {
            file = stdin;
            SET_BINMODE(stdin);
          }
          else {
            file = fopen(p, "rb");
            if(!file)
              warnf(config,
                    "Couldn't read data from file \"%s\", this makes "
                    "an empty POST.\n", nextarg);
          }

          err = file2memory(&postdata, &size, file);

          if(file && (file != stdin))
            fclose(file);
          if(err)
            return err;
        }
        else {
          GetStr(&postdata, p);
          size = strlen(postdata);
        }

        if(!postdata) {
          /* no data from the file, point to a zero byte string to make this
             get sent as a POST anyway */
          postdata=strdup("");
        }
        else {
          char *enc = curl_easy_escape(config->easy, postdata, (int)size);
          free(postdata); /* no matter if it worked or not */
          if(enc) {
            /* now make a string with the name from above and append the
               encoded string */
            size_t outlen = nlen + strlen(enc) + 2;
            char *n = malloc(outlen);
            if(!n) {
              curl_free(enc);
              return PARAM_NO_MEM;
            }
            if(nlen > 0) /* only append '=' if we have a name */
              snprintf(n, outlen, "%.*s=%s", nlen, nextarg, enc);
            else
              strcpy(n, enc);
            curl_free(enc);
            postdata = n;
          }
          else
            return PARAM_NO_MEM;
        }
      }
      else if('@' == *nextarg) {
        size_t size = 0;
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        nextarg++; /* pass the @ */

        if(curlx_strequal("-", nextarg)) {
          file = stdin;
          if(subletter == 'b') /* forced data-binary */
            SET_BINMODE(stdin);
        }
        else {
          file = fopen(nextarg, "rb");
          if(!file)
            warnf(config, "Couldn't read data from file \"%s\", this makes "
                  "an empty POST.\n", nextarg);
        }

        if(subletter == 'b') {
          /* forced binary */
          err = file2memory(&postdata, &size, file);
          config->postfieldsize = (curl_off_t)size;
        }
        else
          err = file2string(&postdata, file);

        if(file && (file != stdin))
          fclose(file);
        if(err)
          return err;

        if(!postdata) {
          /* no data from the file, point to a zero byte string to make this
             get sent as a POST anyway */
          postdata=strdup("");
        }
      }
      else {
        GetStr(&postdata, nextarg);
      }

#ifdef CURL_DOES_CONVERSIONS
      if(subletter != 'b') { /* NOT forced binary, convert to ASCII */
        convert_to_network(postdata, strlen(postdata));
      }
#endif

      if(config->postfields) {
        /* we already have a string, we append this one
           with a separating &-letter */
        char *oldpost=config->postfields;
        size_t newlen = strlen(oldpost) + strlen(postdata) + 2;
        config->postfields=malloc(newlen);
        if(!config->postfields) {
          free(postdata);
          return PARAM_NO_MEM;
        }
        /* use ASCII value 0x26 for '&' to accommodate non-ASCII platforms */
        snprintf(config->postfields, newlen, "%s\x26%s", oldpost, postdata);
        free(oldpost);
        free(postdata);
      }
      else
        config->postfields=postdata;
    }
    /*
      We can't set the request type here, as this data might be used in
      a simple GET if -G is used. Already or soon.

      if(SetHTTPrequest(HTTPREQ_SIMPLEPOST, &config->httpreq))
      return PARAM_BAD_USE;
    */
    break;
    case 'D':
      /* dump-header to given file name */
      GetStr(&config->headerfile, nextarg);
      break;
    case 'e':
    {
      char *ptr = strstr(nextarg, ";auto");
      if(ptr) {
        /* Automatic referer requested, this may be combined with a
           set initial one */
        config->autoreferer = TRUE;
        *ptr = 0; /* zero terminate here */
      }
      else
        config->autoreferer = FALSE;
      GetStr(&config->referer, nextarg);
    }
    break;
    case 'E':
      switch(subletter) {
      case 'a': /* CA info PEM file */
        /* CA info PEM file */
        GetStr(&config->cacert, nextarg);
        break;
