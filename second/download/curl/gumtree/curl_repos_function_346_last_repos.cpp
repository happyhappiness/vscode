const char *
Curl_os400_zlibVersion(void)

{
  return set_thread_string(LK_ZLIB_VERSION, zlibVersion());
}