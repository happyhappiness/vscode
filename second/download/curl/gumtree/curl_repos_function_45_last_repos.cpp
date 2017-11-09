static long file_is_coming(struct curl_fileinfo *finfo,
                           struct callback_data *data,
                           int remains)
{
  printf("%3d %40s %10luB ", remains, finfo->filename,
         (unsigned long)finfo->size);

  switch(finfo->filetype) {
  case CURLFILETYPE_DIRECTORY:
    printf(" DIR\n");
    break;
  case CURLFILETYPE_FILE:
    printf("FILE ");
    break;
  default:
    printf("OTHER\n");
    break;
  }

  if(finfo->filetype == CURLFILETYPE_FILE) {
    /* do not transfer files >= 50B */
    if(finfo->size > 50) {
      printf("SKIPPED\n");
      return CURL_CHUNK_BGN_FUNC_SKIP;
    }

    data->output = fopen(finfo->filename, "wb");
    if(!data->output) {
      return CURL_CHUNK_BGN_FUNC_FAIL;
    }
  }

  return CURL_CHUNK_BGN_FUNC_OK;
}