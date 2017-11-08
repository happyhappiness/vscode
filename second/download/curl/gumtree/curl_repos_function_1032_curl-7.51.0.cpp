static int h2_session_send(struct Curl_easy *data,
                           nghttp2_session *h2)
{
  struct HTTP *stream = data->req.protop;
  if((data->set.stream_weight != data->state.stream_weight) ||
     (data->set.stream_depends_e != data->state.stream_depends_e) ||
     (data->set.stream_depends_on != data->state.stream_depends_on) ) {
    /* send new weight and/or dependency */
    nghttp2_priority_spec pri_spec;
    int rv;

    h2_pri_spec(data, &pri_spec);

    DEBUGF(infof(data, "Queuing PRIORITY on stream %u (easy %p)\n",
                 stream->stream_id, data));
    rv = nghttp2_submit_priority(h2, NGHTTP2_FLAG_NONE, stream->stream_id,
                                 &pri_spec);
    if(rv)
      return rv;
  }

  return nghttp2_session_send(h2);
}