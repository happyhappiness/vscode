static size_t fuzz_write_callback(void *contents,
                                  size_t size,
                                  size_t nmemb,
                                  void *ptr)
{
  size_t total = size * nmemb;
  FUZZ_DATA *fuzz = (FUZZ_DATA *)ptr;
  size_t copy_len = total;

  /* Restrict copy_len to at most TEMP_WRITE_ARRAY_SIZE. */
  if(copy_len > TEMP_WRITE_ARRAY_SIZE) {
    copy_len = TEMP_WRITE_ARRAY_SIZE;
  }

  /* Copy bytes to the temp store just to ensure the parameters are
     exercised. */
  memcpy(fuzz->write_array, contents, copy_len);

  return total;
}