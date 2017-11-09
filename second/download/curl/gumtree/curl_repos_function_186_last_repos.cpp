int url_feof(URL_FILE *file)
{
  int ret = 0;

  switch(file->type) {
  case CFTYPE_FILE:
    ret = feof(file->handle.file);
    break;

  case CFTYPE_CURL:
    if((file->buffer_pos == 0) && (!file->still_running))
      ret = 1;
    break;

  default: /* unknown or supported type - oh dear */
    ret = -1;
    errno = EBADF;
    break;
  }
  return ret;
}