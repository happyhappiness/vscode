int
Curl_os400_inflate(z_streamp strm, int flush)

{
  z_const char * msgb4 = strm->msg;
  int ret;

  ret = inflate(strm, flush);

  if(strm->msg != msgb4)
    strm->msg = set_thread_string(LK_ZLIB_MSG, strm->msg);

  return ret;
}