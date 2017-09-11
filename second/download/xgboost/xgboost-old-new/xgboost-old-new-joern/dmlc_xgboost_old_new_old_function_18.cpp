virtual size_t Read(void *ptr, size_t size) {
    utils::Error("Base64OutStream do not support read");
    return 0;
  }