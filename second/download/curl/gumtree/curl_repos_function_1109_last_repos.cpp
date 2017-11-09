static void h2_pri_spec(struct Curl_easy *data,
                        nghttp2_priority_spec *pri_spec)
{
  struct HTTP *depstream = (data->set.stream_depends_on?
                            data->set.stream_depends_on->req.protop:NULL);
  int32_t depstream_id = depstream? depstream->stream_id:0;
  nghttp2_priority_spec_init(pri_spec, depstream_id, data->set.stream_weight,
                             data->set.stream_depends_e);
  data->state.stream_weight = data->set.stream_weight;
  data->state.stream_depends_e = data->set.stream_depends_e;
  data->state.stream_depends_on = data->set.stream_depends_on;
}