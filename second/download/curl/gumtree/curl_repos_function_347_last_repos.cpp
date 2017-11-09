int
Curl_os400_inflateInit_(z_streamp strm, const char * version, int stream_size)

{
  z_const char * msgb4 = strm->msg;
  int ret;

  ret = inflateInit(strm);

  if(strm->msg != msgb4)
    strm->msg = set_thread_string(LK_ZLIB_MSG, strm->msg);

  return ret;
}