int cu_tail_readline(cu_tail_t *obj, char *buf, int buflen) {
  int status;

  if (buflen < 1) {
    ERROR("utils_tail: cu_tail_readline: buflen too small: %i bytes.", buflen);
    return (-1);
  }

  if (obj->fh == NULL) {
    status = cu_tail_reopen(obj);
    if (status < 0)
      return (status);
  }
  assert(obj->fh != NULL);

  /* Try to read from the filehandle. If that succeeds, everything appears to
   * be fine and we can return. */
  clearerr(obj->fh);
  if (fgets(buf, buflen, obj->fh) != NULL) {
    buf[buflen - 1] = 0;
    return (0);
  }

  /* Check if we encountered an error */
  if (ferror(obj->fh) != 0) {
    /* Jupp, error. Force `cu_tail_reopen' to reopen the file.. */
    fclose(obj->fh);
    obj->fh = NULL;
  }
  /* else: eof -> check if the file was moved away and reopen the new file if
   * so.. */

  status = cu_tail_reopen(obj);
  /* error -> return with error */
  if (status < 0)
    return (status);
  /* file end reached and file not reopened -> nothing more to read */
  else if (status > 0) {
    buf[0] = 0;
    return (0);
  }

  /* If we get here: file was re-opened and there may be more to read.. Let's
   * try again. */
  if (fgets(buf, buflen, obj->fh) != NULL) {
    buf[buflen - 1] = 0;
    return (0);
  }

  if (ferror(obj->fh) != 0) {
    char errbuf[1024];
    WARNING("utils_tail: fgets (%s) returned an error: %s", obj->file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(obj->fh);
    obj->fh = NULL;
    return (-1);
  }

  /* EOf, well, apparently the new file is empty.. */
  buf[0] = 0;
  return (0);
}