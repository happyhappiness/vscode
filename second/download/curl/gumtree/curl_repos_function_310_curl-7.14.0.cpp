void Curl_pgrsSetDownloadSize(struct SessionHandle *data, curl_off_t size)
{
  data->progress.size_dl = size;
  if(size > 0)
    data->progress.flags |= PGRS_DL_SIZE_KNOWN;
  else
    data->progress.flags &= ~PGRS_DL_SIZE_KNOWN;
}