CF_INLINE void GetDarwinVersionNumber(int *major, int *minor)
{
  int mib[2];
  char *os_version;
  size_t os_version_len;
  char *os_version_major, *os_version_minor/*, *os_version_point*/;

  /* Get the Darwin kernel version from the kernel using sysctl(): */
  mib[0] = CTL_KERN;
  mib[1] = KERN_OSRELEASE;
  if(sysctl(mib, 2, NULL, &os_version_len, NULL, 0) == -1)
    return;
  os_version = malloc(os_version_len*sizeof(char));
  if(!os_version)
    return;
  if(sysctl(mib, 2, os_version, &os_version_len, NULL, 0) == -1) {
    free(os_version);
    return;
  }

  /* Parse the version: */
  os_version_major = strtok(os_version, ".");
  os_version_minor = strtok(NULL, ".");
  /*os_version_point = strtok(NULL, ".");*/
  *major = atoi(os_version_major);
  *minor = atoi(os_version_minor);
  free(os_version);
}