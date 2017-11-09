static size_t write_it(char *buff, size_t size, size_t nmemb,
                       void *cb_data)
{
  struct callback_data *data = cb_data;
  size_t written = 0;
  if(data->output)
    written = fwrite(buff, size, nmemb, data->output);
  else
    /* listing output */
    written = fwrite(buff, size, nmemb, stdout);
  return written;
}