static CURLcode nss_load_ca_certificates(struct connectdata *conn,
                                         int sockindex)
{
  struct Curl_easy *data = conn->data;
  const char *cafile = SSL_CONN_CONFIG(CAfile);
  const char *capath = SSL_CONN_CONFIG(CApath);
  bool use_trust_module;
  CURLcode result = CURLE_OK;

  /* treat empty string as unset */
  if(cafile && !cafile[0])
    cafile = NULL;
  if(capath && !capath[0])
    capath = NULL;

  infof(data, "  CAfile: %s\n  CApath: %s\n",
      cafile ? cafile : "none",
      capath ? capath : "none");

  /* load libnssckbi.so if no other trust roots were specified */
  use_trust_module = !cafile && !capath;

  PR_Lock(nss_trustload_lock);
  if(use_trust_module && !trust_module) {
    /* libnssckbi.so needed but not yet loaded --> load it! */
    result = nss_load_module(&trust_module, trust_library, "trust");
    infof(data, "%s %s\n", (result) ? "failed to load" : "loaded",
          trust_library);
    if(result == CURLE_FAILED_INIT)
      /* make the error non-fatal if we are not going to verify peer */
      result = CURLE_SSL_CACERT_BADFILE;
  }
  else if(!use_trust_module && trust_module) {
    /* libnssckbi.so not needed but already loaded --> unload it! */
    infof(data, "unloading %s\n", trust_library);
    nss_unload_module(&trust_module);
  }
  PR_Unlock(nss_trustload_lock);

  if(cafile)
    result = nss_load_cert(&conn->ssl[sockindex], cafile, PR_TRUE);

  if(result)
    return result;

  if(capath) {
    struct_stat st;
    if(stat(capath, &st) == -1)
      return CURLE_SSL_CACERT_BADFILE;

    if(S_ISDIR(st.st_mode)) {
      PRDirEntry *entry;
      PRDir *dir = PR_OpenDir(capath);
      if(!dir)
        return CURLE_SSL_CACERT_BADFILE;

      while((entry = PR_ReadDir(dir, PR_SKIP_BOTH | PR_SKIP_HIDDEN))) {
        char *fullpath = aprintf("%s/%s", capath, entry->name);
        if(!fullpath) {
          PR_CloseDir(dir);
          return CURLE_OUT_OF_MEMORY;
        }

        if(CURLE_OK != nss_load_cert(&conn->ssl[sockindex], fullpath, PR_TRUE))
          /* This is purposefully tolerant of errors so non-PEM files can
           * be in the same directory */
          infof(data, "failed to load '%s' from CURLOPT_CAPATH\n", fullpath);

        free(fullpath);
      }

      PR_CloseDir(dir);
    }
    else
      infof(data, "warning: CURLOPT_CAPATH not a directory (%s)\n", capath);
  }

  return CURLE_OK;
}