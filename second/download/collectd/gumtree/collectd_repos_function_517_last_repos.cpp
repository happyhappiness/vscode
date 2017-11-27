void cmd_error(cmd_status_t status, cmd_error_handler_t *err,
               const char *format, ...) {
  va_list ap;

  if ((err == NULL) || (err->cb == NULL))
    return;

  va_start(ap, format);
  err->cb(err->ud, status, format, ap);
  va_end(ap);
}