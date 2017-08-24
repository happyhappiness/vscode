(utf16_len > MAX_PATH) {
    /* This should be impossible;  however the CRT has a code path to deal */
    /* with this scenario, so I added a check anyway. */
    return UV_EIO;
  }