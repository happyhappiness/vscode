{
    proxy = strdup(data->set.str[STRING_PROXY]);
    /* if global proxy is set, this is it */
    if(NULL == proxy) {
      failf(data, "memory shortage");
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }
  }