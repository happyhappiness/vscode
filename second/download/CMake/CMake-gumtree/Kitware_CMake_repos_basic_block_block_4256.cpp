{
  case HTTPREQ_POST:
  case HTTPREQ_POST_FORM:
  case HTTPREQ_PUT:
    if(conn->data->state.infilesize != -1)
      stream->upload_left = conn->data->state.infilesize;
    else
      /* data sending without specifying the data amount up front */
      stream->upload_left = -1; /* unknown, but not zero */

    data_prd.read_callback = data_source_read_callback;
    data_prd.source.ptr = NULL;
    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                       &data_prd, conn->data);
    break;
  default:
    stream_id = nghttp2_submit_request(h2, &pri_spec, nva, nheader,
                                       NULL, conn->data);
  }