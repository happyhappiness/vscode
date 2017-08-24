(req->flags & UV_FS_FREE_PTR) {
    if (req->fs_type == UV_FS_SCANDIR && req->ptr != NULL)
      uv__fs_scandir_cleanup(req);
    else
      uv__free(req->ptr);
  }