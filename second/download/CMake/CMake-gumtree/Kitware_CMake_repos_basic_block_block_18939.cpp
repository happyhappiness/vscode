(nbufs > 0) {
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