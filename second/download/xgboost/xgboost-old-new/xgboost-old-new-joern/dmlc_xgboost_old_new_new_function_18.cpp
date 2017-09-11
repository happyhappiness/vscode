virtual size_t Read(void *ptr, size_t size) {
    LOG(FATAL) << "Base64OutStream do not support read";
    return 0;
  }