void cmd_error_fh(void *ud, cmd_status_t status, const char *format,
                  va_list ap) {
  FILE *fh = ud;
  int code = -1;
  char buf[1024];

  if (status == CMD_OK)
    code = 0;

  vsnprintf(buf, sizeof(buf), format, ap);
  buf[sizeof(buf) - 1] = '\0';
  if (fprintf(fh, "%i %s\n", code, buf) < 0) {
    char errbuf[1024];
    WARNING("utils_cmds: failed to write to file-handle #%i: %s", fileno(fh),
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return;
  }

  fflush(fh);
}