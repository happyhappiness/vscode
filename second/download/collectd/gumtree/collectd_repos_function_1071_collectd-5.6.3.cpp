static int version_detect(const char *filename) {
  FILE *fh;
  char buffer[1024];
  int version = 0;

  /* Sanity checking. We're called from the config handling routine, so
   * better play it save. */
  if ((filename == NULL) || (*filename == 0))
    return (0);

  fh = fopen(filename, "r");
  if (fh == NULL) {
    char errbuf[1024];
    WARNING("openvpn plugin: Unable to read \"%s\": %s", filename,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return (0);
  }

  /* now search for the specific multimode data format */
  while ((fgets(buffer, sizeof(buffer), fh)) != NULL) {
    /* we look at the first line searching for SINGLE mode configuration */
    if (strcmp(buffer, VSSTRING) == 0) {
      DEBUG("openvpn plugin: found status file version SINGLE");
      version = SINGLE;
      break;
    }
    /* searching for multi version 1 */
    else if (strcmp(buffer, V1STRING) == 0) {
      DEBUG("openvpn plugin: found status file version MULTI1");
      version = MULTI1;
      break;
    }
    /* searching for multi version 2 */
    else if (strcmp(buffer, V2STRING) == 0) {
      DEBUG("openvpn plugin: found status file version MULTI2");
      version = MULTI2;
      break;
    }
    /* searching for multi version 3 */
    else if (strcmp(buffer, V3STRING) == 0) {
      DEBUG("openvpn plugin: found status file version MULTI3");
      version = MULTI3;
      break;
    }
    /* searching for multi version 4 */
    else if (strcmp(buffer, V4STRING) == 0) {
      DEBUG("openvpn plugin: found status file version MULTI4");
      version = MULTI4;
      break;
    }
  }

  if (version == 0) {
    /* This is only reached during configuration, so complaining to
     * the user is in order. */
    NOTICE("openvpn plugin: %s: Unknown file format, please "
           "report this as bug. Make sure to include "
           "your status file, so the plugin can "
           "be adapted.",
           filename);
  }

  fclose(fh);

  return version;
}