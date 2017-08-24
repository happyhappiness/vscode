(pipe->ipc) {
    if (!(access.AccessFlags & FILE_WRITE_DATA) ||
        !(access.AccessFlags & FILE_READ_DATA)) {
      return UV_EINVAL;
    }
  }