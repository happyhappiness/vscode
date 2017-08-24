{
  const char* buf;
  size_t len;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

#define CHECK_ENV_VAR(name)                                                   \
  do {                                                                        \
    buf = getenv(name);                                                       \
    if (buf != NULL)                                                          \
      goto return_buffer;                                                     \
  }                                                                           \
  while (0)

  /* Check the TMPDIR, TMP, TEMP, and TEMPDIR environment variables in order */
  CHECK_ENV_VAR("TMPDIR");
  CHECK_ENV_VAR("TMP");
  CHECK_ENV_VAR("TEMP");
  CHECK_ENV_VAR("TEMPDIR");

#undef CHECK_ENV_VAR

  /* No temp environment variables defined */
  #if defined(__ANDROID__)
    buf = "/data/local/tmp";
  #else
    buf = "/tmp";
  #endif

return_buffer:
  len = strlen(buf);

  if (len >= *size) {
    *size = len + 1;
    return -ENOBUFS;
  }

  /* The returned directory should not have a trailing slash. */
  if (len > 1 && buf[len - 1] == '/') {
    len--;
  }

  memcpy(buffer, buf, len + 1);
  buffer[len] = '\0';
  *size = len;

  return 0;
}