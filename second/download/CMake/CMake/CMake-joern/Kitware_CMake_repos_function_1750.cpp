static void uv_unique_pipe_name(char* ptr, char* name, size_t size) {
  snprintf(name, size, "\\\\?\\pipe\\uv\\%p-%lu", ptr, GetCurrentProcessId());
}