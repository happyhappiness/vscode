static CURLcode main_init(struct GlobalConfig *config)
{
  CURLcode result = CURLE_OK;

#if defined(__DJGPP__) || defined(__GO32__)
  /* stop stat() wasting time */
  _djstat_flags |= _STAT_INODE | _STAT_EXEC_MAGIC | _STAT_DIRSIZE;
#endif

  /* Initialise the global config */
  config->showerror = -1;             /* Will show errors */
  config->errors = stderr;            /* Default errors to stderr */

  /* Allocate the initial operate config */
  config->first = config->last = malloc(sizeof(struct OperationConfig));
  if(config->first) {
    /* Perform the libcurl initialization */
    result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if(!result) {
      /* Get information about libcurl */
      result = get_libcurl_info();

      if(!result) {
        /* Get a curl handle to use for all forthcoming curl transfers */
        config->easy = curl_easy_init();
        if(config->easy) {
          /* Initialise the config */
          config_init(config->first);
          config->first->easy = config->easy;
          config->first->global = config;
        }
        else {
          helpf(stderr, "error initializing curl easy handle\n");
          result = CURLE_FAILED_INIT;
          free(config->first);
        }
      }
      else {
        helpf(stderr, "error retrieving curl library information\n");
        free(config->first);
      }
    }
    else {
      helpf(stderr, "error initializing curl library\n");
      free(config->first);
    }
  }
  else {
    helpf(stderr, "error initializing curl\n");
    result = CURLE_FAILED_INIT;
  }

  return result;
}