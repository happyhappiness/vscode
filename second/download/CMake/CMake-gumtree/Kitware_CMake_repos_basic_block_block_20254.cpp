(pCreateSymbolicLinkW) {
    result = pCreateSymbolicLinkW(new_pathw,
                                  pathw,
                                  flags & UV_FS_SYMLINK_DIR ? SYMBOLIC_LINK_FLAG_DIRECTORY : 0) ? 0 : -1;
    if (result == -1) {
      SET_REQ_WIN32_ERROR(req, GetLastError());
    } else {
      SET_REQ_RESULT(req, result);
    }
  }