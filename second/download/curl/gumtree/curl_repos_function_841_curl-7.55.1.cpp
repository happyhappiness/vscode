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

  /* Allow strtok() here since this isn't used threaded */
  /* !checksrc! disable BANNEDFUNC 2 */
  tempdir = strtok(outdup, PATH_DELIMITERS);

  while(tempdir != NULL) {
    tempdir2 = strtok(NULL, PATH_DELIMITERS);
    /* since strtok returns a token for the last word even
       if not ending with DIR_CHAR, we need to prune it */
    if(tempdir2 != NULL) {
      size_t dlen = strlen(dirbuildup);
      if(dlen)
        snprintf(&dirbuildup[dlen], outlen - dlen, "%s%s", DIR_CHAR, tempdir);
      else {
        if(outdup == tempdir)
          /* the output string doesn't start with a separator */
          strcpy(dirbuildup, tempdir);
        else
          snprintf(dirbuildup, outlen, "%s%s", DIR_CHAR, tempdir);
      }
      if(access(dirbuildup, F_OK) == -1) {
        if(-1 == mkdir(dirbuildup, (mode_t)0000750)) {
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