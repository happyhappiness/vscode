static int before_frame_send(nghttp2_session *session,
                             const nghttp2_frame *frame,
                             void *userp)
{
  struct Curl_easy *data_s;
  (void)userp;

  data_s = nghttp2_session_get_stream_user_data(session, frame->hd.stream_id);
  if(data_s) {
    DEBUGF(infof(data_s, "before_frame_send() was called\n"));
  }

  return 0;
}