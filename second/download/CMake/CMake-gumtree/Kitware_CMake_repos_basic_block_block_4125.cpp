{
  /* Verify that we got a good easy handle in the push header struct, mostly to
     detect rubbish input fast(er). */
  if(!h || !GOOD_EASY_HANDLE(h->data))
    return NULL;
  else {
    struct HTTP *stream = h->data->req.protop;
    if(num < stream->push_headers_used)
      return stream->push_headers[num];
  }
  return NULL;
}