void Curl_pgrsSetUploadSize(struct SessionHandle *data, curl_off_t size)
{
  data->progress.size_ul = size;
  if(size > 0)
    data->progress.flags |= PGRS_UL_SIZE_KNOWN;
  else
    data->progress.flags &= ~PGRS_UL_SIZE_KNOWN;
}