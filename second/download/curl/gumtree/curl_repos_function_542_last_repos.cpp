int gethostname(char *name, GETHOSTNAME_TYPE_ARG2 namelen)
{
  const char *force_hostname = getenv("CURL_GETHOSTNAME");
  if(force_hostname) {
    strncpy(name, force_hostname, namelen);
    name[namelen-1] = '\0';
    return 0;
  }

  /* LD_PRELOAD used, but no hostname set, we'll just return a failure */
  return -1;
}