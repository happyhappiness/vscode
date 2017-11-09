static long file_is_downloaded(struct callback_data *data)
{
  if(data->output) {
    printf("DOWNLOADED\n");
    fclose(data->output);
    data->output = 0x0;
  }
  return CURL_CHUNK_END_FUNC_OK;
}