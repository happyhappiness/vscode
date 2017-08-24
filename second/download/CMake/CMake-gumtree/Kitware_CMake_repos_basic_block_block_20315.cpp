{
  int err;

  uv_fs_req_init(loop, req, UV_FS_ACCESS, cb);

  err = fs__capture_path(req, path, NULL, cb != NULL);
  if (err)
    return uv_translate_sys_error(err);

  req->fs.info.mode = flags;

  if (cb) {
    QUEUE_FS_TP_JOB(loop, req);
    return 0;
  }

  fs__access(req);
  return req->result;
}