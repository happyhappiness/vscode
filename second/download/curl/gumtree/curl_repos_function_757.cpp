CURLcode create_dir_hierarchy(const char *outfile, FILE *errors)
{
  char *tempdir;
  char *tempdir2;
  char *outdup;
  char *dirbuildup;
  CURLcode result = CURLE_OK;
  size_t outlen;

  outlen = strlen(outfile);
  outdup = strdup(outfile);
  if(!outdup)
    return CURLE_OUT_OF_MEMORY;

  dirbuildup = malloc(outlen + 1);
  if(!dirbuildup) {
    Curl_safefree(outdup);
    return CURLE_OUT_OF_MEMORY;
  }
  dirbuildup[0] = '\0';

  tempdir = strtok(outdup, DIR_CHAR);

  while(tempdir != NULL) {
    tempdir2 = strtok(NULL, DIR_CHAR);
    /* since strtok returns a token for the last word even
       if not ending with DIR_CHAR, we need to prune it */
    if(tempdir2 != NULL) {
      size_t dlen = strlen(dirbuildup);
      if(dlen)
        snprintf(&dirbuildup[dlen], outlen - dlen, "%s%s", DIR_CHAR, tempdir);
      else {
        if(0 != strncmp(outdup, DIR_CHAR, 1))
          strcpy(dirbuildup, tempdir);
        else
          snprintf(dirbuildup, outlen, "%s%s", DIR_CHAR, tempdir);
      }
      if(access(dirbuildup, F_OK) == -1) {
        if(-1 == mkdir(dirbuildup,(mode_t)0000750)) {
          show_dir_errno(errors, dirbuildup);
          result = CURLE_WRITE_ERROR;
          break; /* get out of loop */
        }
      }
    }
    tempdir = tempdir2;
  }

  Curl_safefree(dirbuildup);
  Curl_safefree(outdup);

  return result;
}