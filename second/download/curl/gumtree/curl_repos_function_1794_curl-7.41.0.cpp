static CURLcode init_wc_data(struct connectdata *conn)
{
  char *last_slash;
  char *path = conn->data->state.path;
  struct WildcardData *wildcard = &(conn->data->wildcard);
  CURLcode result = CURLE_OK;
  struct ftp_wc_tmpdata *ftp_tmp;

  last_slash = strrchr(conn->data->state.path, '/');
  if(last_slash) {
    last_slash++;
    if(last_slash[0] == '\0') {
      wildcard->state = CURLWC_CLEAN;
      result = ftp_parse_url_path(conn);
      return result;
    }
    else {
      wildcard->pattern = strdup(last_slash);
      if(!wildcard->pattern)
        return CURLE_OUT_OF_MEMORY;
      last_slash[0] = '\0'; /* cut file from path */
    }
  }
  else { /* there is only 'wildcard pattern' or nothing */
    if(path[0]) {
      wildcard->pattern = strdup(path);
      if(!wildcard->pattern)
        return CURLE_OUT_OF_MEMORY;
      path[0] = '\0';
    }
    else { /* only list */
      wildcard->state = CURLWC_CLEAN;
      result = ftp_parse_url_path(conn);
      return result;
    }
  }

  /* program continues only if URL is not ending with slash, allocate needed
     resources for wildcard transfer */

  /* allocate ftp protocol specific temporary wildcard data */
  ftp_tmp = calloc(1, sizeof(struct ftp_wc_tmpdata));
  if(!ftp_tmp) {
    Curl_safefree(wildcard->pattern);
    return CURLE_OUT_OF_MEMORY;
  }

  /* INITIALIZE parselist structure */
  ftp_tmp->parser = Curl_ftp_parselist_data_alloc();
  if(!ftp_tmp->parser) {
    Curl_safefree(wildcard->pattern);
    Curl_safefree(ftp_tmp);
    return CURLE_OUT_OF_MEMORY;
  }

  wildcard->tmp = ftp_tmp; /* put it to the WildcardData tmp pointer */
  wildcard->tmp_dtor = wc_data_dtor;

  /* wildcard does not support NOCWD option (assert it?) */
  if(conn->data->set.ftp_filemethod == FTPFILE_NOCWD)
    conn->data->set.ftp_filemethod = FTPFILE_MULTICWD;

  /* try to parse ftp url */
  result = ftp_parse_url_path(conn);
  if(result) {
    Curl_safefree(wildcard->pattern);
    wildcard->tmp_dtor(wildcard->tmp);
    wildcard->tmp_dtor = ZERO_NULL;
    wildcard->tmp = NULL;
    return result;
  }

  wildcard->path = strdup(conn->data->state.path);
  if(!wildcard->path) {
    Curl_safefree(wildcard->pattern);
    wildcard->tmp_dtor(wildcard->tmp);
    wildcard->tmp_dtor = ZERO_NULL;
    wildcard->tmp = NULL;
    return CURLE_OUT_OF_MEMORY;
  }

  /* backup old write_function */
  ftp_tmp->backup.write_function = conn->data->set.fwrite_func;
  /* parsing write function */
  conn->data->set.fwrite_func = Curl_ftp_parselist;
  /* backup old file descriptor */
  ftp_tmp->backup.file_descriptor = conn->data->set.out;
  /* let the writefunc callback know what curl pointer is working with */
  conn->data->set.out = conn;

  infof(conn->data, "Wildcard - Parsing started\n");
  return CURLE_OK;
}