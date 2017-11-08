static void PL_ERROR(struct connectdata *conn, CURLcode err)
{
  struct ftp_wc_tmpdata *tmpdata = conn->data->wildcard.tmp;
  struct ftp_parselist_data *parser = tmpdata->parser;
  if(parser->file_data)
    Curl_fileinfo_dtor(NULL, parser->file_data);
  parser->file_data = NULL;
  parser->error = err;
}