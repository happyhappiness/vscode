{
  if (bufs == NULL || nbufs == 0)
    return -EINVAL;

  INIT(READ);
  req->file = file;

  req->nbufs = nbufs;
  req->bufs = req->bufsml;
  if (nbufs > ARRAY_SIZE(req->bufsml))
    req->bufs = uv__malloc(nbufs * sizeof(*bufs));

  if (req->bufs == NULL) {
    if (cb != NULL)
      uv__req_unregister(loop, req);
    return -ENOMEM;
  }

  memcpy(req->bufs, bufs, nbufs * sizeof(*bufs));

  req->off = off;
  POST;
}