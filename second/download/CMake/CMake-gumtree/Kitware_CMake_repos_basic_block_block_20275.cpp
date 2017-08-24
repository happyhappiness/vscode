{
  if (bufs == NULL || nbufs == 0)
    return UV_EINVAL;

  uv_fs_req_init(loop, req, UV_FS_READ, cb);

  req->file.fd = fd;

  req->fs.info.nbufs = nbufs;
  req->fs.info.bufs = req->fs.info.bufsml;
  if (nbufs > ARRAY_SIZE(req->fs.info.bufsml))
    req->fs.info.bufs = uv__malloc(nbufs * sizeof(*bufs));

  if (req->fs.info.bufs == NULL)
    return UV_ENOMEM;

  memcpy(req->fs.info.bufs, bufs, nbufs * sizeof(*bufs));

  req->fs.info.offset = offset;

  if (cb) {
    QUEUE_FS_TP_JOB(loop, req);
    return 0;
  } else {
    fs__read(req);
    return req->result;
  }
}