void pgrsSetUploadSize(struct UrlData *data, double size)
{
  if(size > 0) {
    data->progress.size_ul = size;
    data->progress.flags |= PGRS_UL_SIZE_KNOWN;
  }
}