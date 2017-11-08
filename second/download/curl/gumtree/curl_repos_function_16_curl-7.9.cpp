size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}