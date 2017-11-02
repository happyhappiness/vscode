static bool ftp_endofresp(struct connectdata *conn, char *line, size_t len,
                          int *code)
{
  (void)conn;

  if((len > 3) && LASTLINE(line)) {
    *code = curlx_sltosi(strtol(line, NULL, 10));
    return TRUE;
  }

  return FALSE;
}