int
Curl_os400_inflateEnd(z_streamp strm)

{
  z_const char * msgb4 = strm->msg;
  int ret;

  ret = inflateEnd(strm);

  if(strm->msg != msgb4)
    strm->msg = set_thread_string(LK_ZLIB_MSG, strm->msg);

  return ret;
}