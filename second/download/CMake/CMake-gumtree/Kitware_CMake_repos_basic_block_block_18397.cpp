{
  struct poll_ctx* ctx;
  size_t required_len;

  if (!uv__is_active(handle)) {
    *size = 0;
    return UV_EINVAL;
  }

  ctx = handle->poll_ctx;
  assert(ctx != NULL);

  required_len = strlen(ctx->path);
  if (required_len >= *size) {
    *size = required_len + 1;
    return UV_ENOBUFS;
  }

  memcpy(buffer, ctx->path, required_len);
  *size = required_len;
  buffer[required_len] = '\0';

  return 0;
}