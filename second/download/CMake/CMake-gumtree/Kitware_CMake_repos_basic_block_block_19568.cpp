{
    uv__req_unregister(stream->loop, stream->connect_req);
    stream->connect_req->cb(stream->connect_req, -ECANCELED);
    stream->connect_req = NULL;
  }