static CURLcode ftp_pl_insert_finfo(struct connectdata *conn,
                                    struct fileinfo *infop)
{
  curl_fnmatch_callback compare;
  struct WildcardData *wc = &conn->data->wildcard;
  struct ftp_wc_tmpdata *tmpdata = wc->tmp;
  struct curl_llist *llist = &wc->filelist;
  struct ftp_parselist_data *parser = tmpdata->parser;
  bool add = TRUE;
  struct curl_fileinfo *finfo = &infop->info;

  /* move finfo pointers to b_data */
  char *str = finfo->b_data;
  finfo->filename       = str + parser->offsets.filename;
  finfo->strings.group  = parser->offsets.group ?
                          str + parser->offsets.group : NULL;
  finfo->strings.perm   = parser->offsets.perm ?
                          str + parser->offsets.perm : NULL;
  finfo->strings.target = parser->offsets.symlink_target ?
                          str + parser->offsets.symlink_target : NULL;
  finfo->strings.time   = str + parser->offsets.time;
  finfo->strings.user   = parser->offsets.user ?
                          str + parser->offsets.user : NULL;

  /* get correct fnmatch callback */
  compare = conn->data->set.fnmatch;
  if(!compare)
    compare = Curl_fnmatch;

  /* filter pattern-corresponding filenames */
  if(compare(conn->data->set.fnmatch_data, wc->pattern,
             finfo->filename) == 0) {
    /* discard symlink which is containing multiple " -> " */
    if((finfo->filetype == CURLFILETYPE_SYMLINK) && finfo->strings.target &&
       (strstr(finfo->strings.target, " -> "))) {
      add = FALSE;
    }
  }
  else {
    add = FALSE;
  }

  if(add) {
    Curl_llist_insert_next(llist, llist->tail, finfo, &infop->list);
  }
  else {
    Curl_fileinfo_dtor(NULL, finfo);
  }

  tmpdata->parser->file_data = NULL;
  return CURLE_OK;
}