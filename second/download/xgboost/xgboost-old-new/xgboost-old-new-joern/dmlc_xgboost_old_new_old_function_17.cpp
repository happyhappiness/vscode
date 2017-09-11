virtual void Write(const void *ptr, size_t size) {
    utils::Error("Base64InStream do not support write");
  }