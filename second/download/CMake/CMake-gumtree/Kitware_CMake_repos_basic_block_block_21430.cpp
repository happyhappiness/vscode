(len > MAX_PATH) {
    /* This should not be possible */
    return UV_EIO;
  }