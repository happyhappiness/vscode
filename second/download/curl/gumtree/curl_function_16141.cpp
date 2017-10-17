static void ossl_keylog_callback(const SSL *ssl, const char *line)
{
  (void)ssl;

  /* Using fputs here instead of fprintf since libcurl's fprintf replacement
     may not be thread-safe. */
  if(keylog_file_fp && line && *line) {
    char stackbuf[256];
    char *buf;
    size_t linelen = strlen(line);

    if(linelen <= sizeof(stackbuf) - 2)
      buf = stackbuf;
    else {
      buf = malloc(linelen + 2);
      if(!buf)
        return;
    }
    strncpy(buf, line, linelen);
    buf[linelen] = '\n';
    buf[linelen + 1] = '\0';

    fputs(buf, keylog_file_fp);
    if(buf != stackbuf)
      free(buf);
  }
}