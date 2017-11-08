static int on_invalid_frame_recv(nghttp2_session *session,
                                 const nghttp2_frame *frame,
                                 int lib_error_code, void *userp)
{
  struct Curl_easy *data_s = NULL;
  (void)userp;
#if !defined(DEBUGBUILD) || defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void)lib_error_code;
#endif

  data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
  if(data_s) {
    DEBUGF(infof(data_s,
                 "on_invalid_frame_recv() was called, error=%d:%s\n",
                 lib_error_code, nghttp2_strerror(lib_error_code)));
  }
  return 0;
}