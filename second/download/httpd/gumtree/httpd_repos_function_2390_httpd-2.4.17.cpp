static int on_begin_headers_cb(nghttp2_session *ngh2,
                               const nghttp2_frame *frame, void *userp)
{
    /* This starts a new stream. */
    int rv;
    (void)ngh2;
    rv = stream_open((h2_session *)userp, frame->hd.stream_id);
    if (rv != NGHTTP2_ERR_CALLBACK_FAILURE) {
      /* on_header_cb or on_frame_recv_cb will dectect that stream
         does not exist and submit RST_STREAM. */
      return 0;
    }
    return NGHTTP2_ERR_CALLBACK_FAILURE;
}