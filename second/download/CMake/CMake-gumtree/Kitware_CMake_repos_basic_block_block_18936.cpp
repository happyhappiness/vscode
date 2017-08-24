{
  unsigned int iovmax;
  unsigned int nbufs;
  uv_buf_t* bufs;
  ssize_t total;
  ssize_t result;

  iovmax = uv__getiovmax();
  nbufs = req->nbufs;
  bufs = req->bufs;
  total = 0;

  while (nbufs > 0) {
    req->nbufs = nbufs;
    if (req->nbufs > iovmax)
      req->nbufs = iovmax;

    result = process(req);
    if (result <= 0) {
      if (total == 0)
        total = result;
      break;
    }

    if (req->off >= 0)
      req->off += result;

    req->bufs += req->nbufs;
    nbufs -= req->nbufs;
    total += result;
  }

  if (errno == EINTR && total == -1)
    return total;

  if (bufs != req->bufsml)
    uv__free(bufs);

  req->bufs = NULL;
  req->nbufs = 0;

  return total;
}