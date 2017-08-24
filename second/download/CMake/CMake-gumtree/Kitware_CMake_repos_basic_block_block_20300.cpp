{
  int err;

  if (!req || !path) {
    return UV_EINVAL;
  }

  uv_fs_req_init(loop, req, UV_FS_REALPATH, cb);

  err = fs__capture_path(req, path, NULL, cb != NULL);
  if (err) {
    return uv_translate_sys_error(err);
  }

  if (cb) {
    QUEUE_FS_TP_JOB(loop, req);
    return 0;
  } else {
    fs__realpath(req);
    return req->result;
  }
}