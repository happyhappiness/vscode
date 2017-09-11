virtual void Write(const void *ptr, size_t size) {
    LOG(FATAL) << "Base64InStream do not support write";
  }