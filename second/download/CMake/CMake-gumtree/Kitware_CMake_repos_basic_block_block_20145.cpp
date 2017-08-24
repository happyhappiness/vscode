(buf_sz == 0) {
    req->file.pathw = NULL;
    req->fs.info.new_pathw = NULL;
    req->path = NULL;
    return 0;
  }