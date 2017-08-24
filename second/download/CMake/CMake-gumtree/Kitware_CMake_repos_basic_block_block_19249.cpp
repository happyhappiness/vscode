{
  int mib[4];
  char **argsbuf = NULL;
  char **argsbuf_tmp;
  size_t argsbuf_size = 100U;
  size_t exepath_size;
  pid_t mypid;
  int err;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  mypid = getpid();
  for (;;) {
    err = -ENOMEM;
    argsbuf_tmp = uv__realloc(argsbuf, argsbuf_size);
    if (argsbuf_tmp == NULL)
      goto out;
    argsbuf = argsbuf_tmp;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC_ARGS;
    mib[2] = mypid;
    mib[3] = KERN_PROC_ARGV;
    if (sysctl(mib, 4, argsbuf, &argsbuf_size, NULL, 0) == 0) {
      break;
    }
    if (errno != ENOMEM) {
      err = -errno;
      goto out;
    }
    argsbuf_size *= 2U;
  }

  if (argsbuf[0] == NULL) {
    err = -EINVAL;  /* FIXME(bnoordhuis) More appropriate error. */
    goto out;
  }

  *size -= 1;
  exepath_size = strlen(argsbuf[0]);
  if (*size > exepath_size)
    *size = exepath_size;

  memcpy(buffer, argsbuf[0], *size);
  buffer[*size] = '\0';
  err = 0;

out:
  uv__free(argsbuf);

  return err;
}