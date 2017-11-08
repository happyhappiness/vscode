void Curl_pgrsSetUploadSize(struct SessionHandle *data, curl_off_t size)
{
  if(size >= 0) {
    data->progress.size_ul = size;
    data->progress.flags |= PGRS_UL_SIZE_KNOWN;
  }
  else {
    data->progress.size_ul = 0;
    data->progress.flags &= ~PGRS_UL_SIZE_KNOWN;
  }
}