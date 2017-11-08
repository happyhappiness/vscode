static void FindWin32CACert(struct Configurable *config, 
                            const char *bundle_file)
{
  curl_version_info_data *info;
  info = curl_version_info(CURLVERSION_NOW);

  /* only check for cert file if "we" support SSL */
  if(info->features & CURL_VERSION_SSL) {
    DWORD buflen;
    char *ptr = NULL;
    char *retval = (char *) malloc(sizeof (TCHAR) * (MAX_PATH + 1));
    if (!retval)
      return;
    retval[0] = '\0';
    buflen = SearchPathA(NULL, bundle_file, NULL, MAX_PATH+2, retval, &ptr);
    if (buflen > 0) {
      GetStr(&config->cacert, retval);
    }
    free(retval);
  }
}