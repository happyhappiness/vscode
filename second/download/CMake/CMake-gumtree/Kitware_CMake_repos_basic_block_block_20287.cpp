(cb) {
    QUEUE_FS_TP_JOB(loop, req);
    return 0;
  } else {
    fs__mkdtemp(req);
    return req->result;
  }