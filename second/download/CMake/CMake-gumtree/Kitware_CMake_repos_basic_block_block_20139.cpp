{
    memcpy(pos, path, path_len);
    assert(path_len == buf_sz - (pos - buf));
    req->path = pos;
  }