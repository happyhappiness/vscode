static size_t fuzz_read_callback(char *buffer,
                                 size_t size,
                                 size_t nitems,
                                 void *ptr)
{
  FUZZ_DATA *fuzz = (FUZZ_DATA *)ptr;
  curl_off_t nread;

  /* If no upload data has been specified, then return an error code. */
  if(fuzz->upload1_data_len == 0) {
    /* No data to upload */
    return CURL_READFUNC_ABORT;
  }

  /* Send the upload data. */
  memcpy(buffer,
         fuzz->upload1_data,
         fuzz->upload1_data_len);

  return fuzz->upload1_data_len;
}