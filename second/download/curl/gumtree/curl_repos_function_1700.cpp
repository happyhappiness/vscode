void Curl_ftp_parselist_data_free(struct ftp_parselist_data **pl_data)
{
  if(*pl_data)
    free(*pl_data);
  *pl_data = NULL;
}