int formparse(struct OperationConfig *config,
              const char *input,
              curl_mime **mimepost,
              curl_mime **mimecurrent,
              bool literal_value)
{
  /* input MUST be a string in the format 'name=contents' and we'll
     build a linked list with the info */
  char *name = NULL;
  char *contents = NULL;
  char *contp;
  char *data;
  char *type = NULL;
  char *filename = NULL;
  char *encoder = NULL;
  struct curl_slist *headers = NULL;
  curl_mimepart *part = NULL;
  CURLcode res;
  int sep = '\0';

  /* Allocate the main mime structure if needed. */
  if(!*mimepost) {
    *mimepost = curl_mime_init(config->easy);
    if(!*mimepost) {
      warnf(config->global, "curl_mime_init failed!\n");
      return 1;
    }
    *mimecurrent = *mimepost;
  }

  /* Make a copy we can overwrite. */
  contents = strdup(input);
  if(!contents) {
    fprintf(config->global->errors, "out of memory\n");
    return 2;
  }

  /* Scan for the end of the name. */
  contp = strchr(contents, '=');
  if(contp) {
    if(contp > contents)
      name = contents;
    *contp++ = '\0';

    if(*contp == '(' && !literal_value) {
      curl_mime *subparts;

      /* Starting a multipart. */
      sep = get_param_part(config, &contp, &data, &type, NULL, NULL, &headers);
      if(sep < 0) {
        Curl_safefree(contents);
        return 3;
      }
      subparts = curl_mime_init(config->easy);
      if(!subparts) {
        warnf(config->global, "curl_mime_init failed!\n");
        curl_slist_free_all(headers);
        Curl_safefree(contents);
        return 4;
      }
      part = curl_mime_addpart(*mimecurrent);
      if(!part) {
        warnf(config->global, "curl_mime_addpart failed!\n");
        curl_mime_free(subparts);
        curl_slist_free_all(headers);
        Curl_safefree(contents);
        return 5;
      }
      if(curl_mime_subparts(part, subparts)) {
        warnf(config->global, "curl_mime_subparts failed!\n");
        curl_mime_free(subparts);
        curl_slist_free_all(headers);
        Curl_safefree(contents);
        return 6;
      }
      *mimecurrent = subparts;
      if(curl_mime_headers(part, headers, 1)) {
        warnf(config->global, "curl_mime_headers failed!\n");
        curl_slist_free_all(headers);
        Curl_safefree(contents);
        return 7;
      }
      if(curl_mime_type(part, type)) {
        warnf(config->global, "curl_mime_type failed!\n");
        Curl_safefree(contents);
        return 8;
      }
    }
    else if(!name && !strcmp(contp, ")") && !literal_value) {
      /* Ending a mutipart. */
      if(*mimecurrent == *mimepost) {
        warnf(config->global, "no multipart to terminate!\n");
        Curl_safefree(contents);
        return 9;
        }
      *mimecurrent = (*mimecurrent)->parent->parent;
    }
    else if('@' == contp[0] && !literal_value) {

      /* we use the @-letter to indicate file name(s) */

      curl_mime *subparts = NULL;

      do {
        /* since this was a file, it may have a content-type specifier
           at the end too, or a filename. Or both. */
        ++contp;
        sep = get_param_part(config, &contp,
                             &data, &type, &filename, &encoder, &headers);
        if(sep < 0) {
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          Curl_safefree(contents);
          return 10;
        }

        /* now contp point to comma or string end.
           If more files to come, make sure we have multiparts. */
        if(!subparts) {
          if(sep != ',')    /* If there is a single file. */
            subparts = *mimecurrent;
          else {
            subparts = curl_mime_init(config->easy);
            if(!subparts) {
              warnf(config->global, "curl_mime_init failed!\n");
              curl_slist_free_all(headers);
              Curl_safefree(contents);
              return 11;
            }
          }
        }

        /* Allocate a part for that file. */
        part = curl_mime_addpart(subparts);
        if(!part) {
          warnf(config->global, "curl_mime_addpart failed!\n");
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          curl_slist_free_all(headers);
          Curl_safefree(contents);
          return 12;
        }

        /* Set part headers. */
        if(curl_mime_headers(part, headers, 1)) {
          warnf(config->global, "curl_mime_headers failed!\n");
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          curl_slist_free_all(headers);
          Curl_safefree(contents);
          return 13;
        }

        /* Setup file in part. */
        res = file_or_stdin(part, data);
        if(res) {
          warnf(config->global, "setting file %s  failed!\n", data);
          if(res != CURLE_READ_ERROR) {
            if(subparts != *mimecurrent)
              curl_mime_free(subparts);
            Curl_safefree(contents);
            return 14;
          }
        }
        if(filename && curl_mime_filename(part, filename)) {
          warnf(config->global, "curl_mime_filename failed!\n");
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          Curl_safefree(contents);
          return 15;
        }
        if(curl_mime_type(part, type)) {
          warnf(config->global, "curl_mime_type failed!\n");
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          Curl_safefree(contents);
          return 16;
        }
        if(curl_mime_encoder(part, encoder)) {
          warnf(config->global, "curl_mime_encoder failed!\n");
          if(subparts != *mimecurrent)
            curl_mime_free(subparts);
          Curl_safefree(contents);
          return 17;
        }

        /* *contp could be '\0', so we just check with the delimiter */
      } while(sep); /* loop if there's another file name */

      /* now we add the multiple files section */
      if(subparts != *mimecurrent) {
        part = curl_mime_addpart(*mimecurrent);
        if(!part) {
          warnf(config->global, "curl_mime_addpart failed!\n");
          curl_mime_free(subparts);
          Curl_safefree(contents);
          return 18;
        }
        if(curl_mime_subparts(part, subparts)) {
          warnf(config->global, "curl_mime_subparts failed!\n");
          curl_mime_free(subparts);
          Curl_safefree(contents);
          return 19;
        }
      }
    }
    else {
        /* Allocate a mime part. */
        part = curl_mime_addpart(*mimecurrent);
        if(!part) {
          warnf(config->global, "curl_mime_addpart failed!\n");
          Curl_safefree(contents);
          return 20;
        }

      if(*contp == '<' && !literal_value) {
        ++contp;
        sep = get_param_part(config, &contp,
                             &data, &type, &filename, &encoder, &headers);
        if(sep < 0) {
          Curl_safefree(contents);
          return 21;
        }

        /* Set part headers. */
        if(curl_mime_headers(part, headers, 1)) {
          warnf(config->global, "curl_mime_headers failed!\n");
          curl_slist_free_all(headers);
          Curl_safefree(contents);
          return 22;
        }

        /* Setup file in part. */
        res = file_or_stdin(part, data);
        if(res) {
          warnf(config->global, "setting file %s failed!\n", data);
          if(res != CURLE_READ_ERROR) {
            Curl_safefree(contents);
            return 23;
          }
        }
      }
      else {
        if(literal_value)
          data = contp;
        else {
          sep = get_param_part(config, &contp,
                               &data, &type, &filename, &encoder, &headers);
          if(sep < 0) {
            Curl_safefree(contents);
            return 24;
          }
        }

        /* Set part headers. */
        if(curl_mime_headers(part, headers, 1)) {
          warnf(config->global, "curl_mime_headers failed!\n");
          curl_slist_free_all(headers);
          Curl_safefree(contents);
          return 25;
        }

#ifdef CURL_DOES_CONVERSIONS
        if(convert_to_network(data, strlen(data))) {
          warnf(config->global, "curl_formadd failed!\n");
          Curl_safefree(contents);
          return 26;
        }
#endif

        if(curl_mime_data(part, data, CURL_ZERO_TERMINATED)) {
          warnf(config->global, "curl_mime_data failed!\n");
          Curl_safefree(contents);
          return 27;
        }
      }

      if(curl_mime_filename(part, filename)) {
        warnf(config->global, "curl_mime_filename failed!\n");
        Curl_safefree(contents);
        return 28;
      }
      if(curl_mime_type(part, type)) {
        warnf(config->global, "curl_mime_type failed!\n");
        Curl_safefree(contents);
        return 29;
      }
      if(curl_mime_encoder(part, encoder)) {
        warnf(config->global, "curl_mime_encoder failed!\n");
        Curl_safefree(contents);
        return 30;
      }

      if(sep) {
        *contp = (char) sep;
        warnf(config->global,
              "garbage at end of field specification: %s\n", contp);
      }
    }

    /* Set part name. */
    if(name && curl_mime_name(part, name)) {
      warnf(config->global, "curl_mime_name failed!\n");
      Curl_safefree(contents);
      return 31;
    }
  }
  else {
    warnf(config->global, "Illegally formatted input field!\n");
    Curl_safefree(contents);
    return 32;
  }
  Curl_safefree(contents);
  return 0;
}