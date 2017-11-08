void main_free(void)
{
  curl_global_cleanup();
  convert_cleanup();
  metalink_cleanup();
}