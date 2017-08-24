{
  int mib[4];
  size_t cb;
  pid_t mypid;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  mypid = getpid();
  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC_ARGS;
  mib[2] = mypid;
  mib[3] = KERN_PROC_ARGV;

  cb = *size;
  if (sysctl(mib, 4, buffer, &cb, NULL, 0))
    return -errno;
  *size = strlen(buffer);

  return 0;
}