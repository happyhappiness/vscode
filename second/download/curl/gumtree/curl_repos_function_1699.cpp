struct ftp_parselist_data *Curl_ftp_parselist_data_alloc(void)
{
  return calloc(1, sizeof(struct ftp_parselist_data));
}