static void wc_data_dtor(void *ptr)
{
  struct ftp_wc_tmpdata *tmp = ptr;
  if(tmp)
    Curl_ftp_parselist_data_free(&tmp->parser);
  Curl_safefree(tmp);
}