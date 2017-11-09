static int on_frame_not_send(nghttp2_session *session,
                             const nghttp2_frame *frame,
                             int lib_error_code, void *userp)
{
  struct Curl_easy *data_s;
  (void)userp;
#if !defined(DEBUGBUILD) || defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void)lib_error_code;
#endif

  data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
  if(data_s) {
    DEBUGF(infof(data_s,
                 "on_frame_not_send() was called, lib_error_code = %d\n",
                 lib_error_code));
  }
  return 0;
}