{
    struct HTTP *stream = h->data->req.protop;
    if(num < stream->push_headers_used)
      return stream->push_headers[num];
  }