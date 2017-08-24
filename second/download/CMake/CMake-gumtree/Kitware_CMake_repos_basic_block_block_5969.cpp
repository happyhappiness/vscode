{
    char *reurl;

    size_t plen = strlen(path); /* new path, should be 1 byte longer than
                                   the original */
    size_t prefixlen = strlen(conn->host.name);

    if(!*prot_missing) {
      size_t protolen = strlen(protop);

      if(curl_strnequal(protop, data->change.url, protolen))
        prefixlen += protolen;
      else {
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }

      if(curl_strnequal("://", &data->change.url[protolen], 3))
        prefixlen += 3;
      /* only file: is allowed to omit one or both slashes */
      else if(curl_strnequal("file:", data->change.url, 5))
        prefixlen += 1 + (data->change.url[5] == '/');
      else {
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }
    }

    reurl = malloc(prefixlen + plen + 1);
    if(!reurl)
      return CURLE_OUT_OF_MEMORY;

    /* copy the prefix */
    memcpy(reurl, data->change.url, prefixlen);

    /* append the trailing piece + zerobyte */
    memcpy(&reurl[prefixlen], path, plen + 1);

    /* possible free the old one */
    if(data->change.url_alloc) {
      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }

    infof(data, "Rebuilt URL to: %s\n", reurl);

    data->change.url = reurl;
    data->change.url_alloc = TRUE; /* free this later */
  }