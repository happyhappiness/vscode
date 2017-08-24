(cb) {
    QUEUE_FS_TP_JOB(loop, req);
    return 0;
  } else {
    fs__chmod(req);
    return req->result;
  }