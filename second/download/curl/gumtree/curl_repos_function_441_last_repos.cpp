static
long chunk_end(void *ptr)
{
  chunk_data_t *ch_d = ptr;
  if(ch_d->print_content) {
    ch_d->print_content = 0;
    printf("-------------------------------------------------------------\n");
  }
  if(ch_d->remains == 1)
    printf("=============================================================\n");
  return CURL_CHUNK_END_FUNC_OK;
}