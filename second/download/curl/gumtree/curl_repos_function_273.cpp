int main(int c, char **argv)
{
  CURL *curlhandle = NULL;

  curl_global_init(CURL_GLOBAL_ALL);
  curlhandle = curl_easy_init();

  upload(curlhandle, "ftp://user:pass@example.com/path/file", "C:\\file", 0, 3);

  curl_easy_cleanup(curlhandle);
  curl_global_cleanup();

  return 0;
}