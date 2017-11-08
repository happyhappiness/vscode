void Curl_pgrsSetDownloadSize(struct SessionHandle *data, double size)
{
  if(size > 0) {
    data->progress.size_dl = size;
    data->progress.flags |= PGRS_DL_SIZE_KNOWN;
  }
}