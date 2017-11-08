CURLcode get_args(struct OperationConfig *config, const size_t i)
{
  CURLcode result = CURLE_OK;
  bool last = (config->next ? FALSE : TRUE);

  /* Check we have a password for the given host user */
  if(config->userpwd && !config->oauth_bearer) {
    result = checkpasswd("host", i, last, &config->userpwd);
    if(result)
      return result;
  }

  /* Check we have a password for the given proxy user */
  if(config->proxyuserpwd) {
    result = checkpasswd("proxy", i, last, &config->proxyuserpwd);
    if(result)
      return result;
  }

  /* Check we have a user agent */
  if(!config->useragent) {
    config->useragent = my_useragent();
    if(!config->useragent) {
      helpf(config->global->errors, "out of memory\n");
      result = CURLE_OUT_OF_MEMORY;
    }
  }

  return result;
}