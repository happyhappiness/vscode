CURLcode FindWin32CACert(struct OperationConfig *config,
                         const char *bundle_file)
{
  CURLcode result = CURLE_OK;

  /* search and set cert file only if libcurl supports SSL */
  if(curlinfo->features & CURL_VERSION_SSL) {

    DWORD res_len;
    char buf[PATH_MAX];
    char *ptr = NULL;

    buf[0] = '\0';

    res_len = SearchPathA(NULL, bundle_file, NULL, PATH_MAX, buf, &ptr);
    if(res_len > 0) {
      Curl_safefree(config->cacert);
      config->cacert = strdup(buf);
      if(!config->cacert)
        result = CURLE_OUT_OF_MEMORY;
    }
  }

  return result;
}