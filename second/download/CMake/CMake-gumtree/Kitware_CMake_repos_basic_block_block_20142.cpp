{
  char* buf;
  char* pos;
  ssize_t buf_sz = 0, path_len = 0, pathw_len = 0, new_pathw_len = 0;

  /* new_path can only be set if path is also set. */
  assert(new_path == NULL || path != NULL);

  if (path != NULL) {
    pathw_len = MultiByteToWideChar(CP_UTF8,
                                    0,
                                    path,
                                    -1,
                                    NULL,
                                    0);
    if (pathw_len == 0) {
      return GetLastError();
    }

    buf_sz += pathw_len * sizeof(WCHAR);
  }

  if (path != NULL && copy_path) {
    path_len = 1 + strlen(path);
    buf_sz += path_len;
  }

  if (new_path != NULL) {
    new_pathw_len = MultiByteToWideChar(CP_UTF8,
                                        0,
                                        new_path,
                                        -1,
                                        NULL,
                                        0);
    if (new_pathw_len == 0) {
      return GetLastError();
    }

    buf_sz += new_pathw_len * sizeof(WCHAR);
  }


  if (buf_sz == 0) {
    req->file.pathw = NULL;
    req->fs.info.new_pathw = NULL;
    req->path = NULL;
    return 0;
  }

  buf = (char*) uv__malloc(buf_sz);
  if (buf == NULL) {
    return ERROR_OUTOFMEMORY;
  }

  pos = buf;

  if (path != NULL) {
    DWORD r = MultiByteToWideChar(CP_UTF8,
                                  0,
                                  path,
                                  -1,
                                  (WCHAR*) pos,
                                  pathw_len);
    assert(r == (DWORD) pathw_len);
    req->file.pathw = (WCHAR*) pos;
    pos += r * sizeof(WCHAR);
  } else {
    req->file.pathw = NULL;
  }

  if (new_path != NULL) {
    DWORD r = MultiByteToWideChar(CP_UTF8,
                                  0,
                                  new_path,
                                  -1,
                                  (WCHAR*) pos,
                                  new_pathw_len);
    assert(r == (DWORD) new_pathw_len);
    req->fs.info.new_pathw = (WCHAR*) pos;
    pos += r * sizeof(WCHAR);
  } else {
    req->fs.info.new_pathw = NULL;
  }

  req->path = path;
  if (path != NULL && copy_path) {
    memcpy(pos, path, path_len);
    assert(path_len == buf_sz - (pos - buf));
    req->path = pos;
  }

  req->flags |= UV_FS_FREE_PATHS;

  return 0;
}