static int openvpn_read(user_data_t *user_data) {
  char buffer[1024];
  int read = 0;

  vpn_status_t *st = user_data->data;

  FILE *fh = fopen(st->file, "r");
  if (fh == NULL) {
    char errbuf[1024];
    WARNING("openvpn plugin: fopen(%s) failed: %s", st->file,
            sstrerror(errno, errbuf, sizeof(errbuf)));

    return -1;
  }

  // Try to detect file format by its first line
  if ((fgets(buffer, sizeof(buffer), fh)) == NULL) {
    WARNING("openvpn plugin: failed to get data from: %s", st->file);
    fclose(fh);
    return -1;
  }

  if (strcmp(buffer, TITLE_SINGLE) == 0) { // OpenVPN STATISTICS
    DEBUG("openvpn plugin: found status file SINGLE");
    read = single_read(st->name, fh);
  } else if (strcmp(buffer, TITLE_V1) == 0) { // OpenVPN CLIENT LIST
    DEBUG("openvpn plugin: found status file MULTI version 1");
    read = multi1_read(st->name, fh);
  } else if (strncmp(buffer, TITLE_V2, strlen(TITLE_V2)) == 0) { // TITLE
    DEBUG("openvpn plugin: found status file MULTI version 2/3");
    read = multi2_read(st->name, fh);
  } else {
    NOTICE("openvpn plugin: %s: Unknown file format, please "
           "report this as bug. Make sure to include "
           "your status file, so the plugin can "
           "be adapted.",
           st->file);
    read = -1;
  }
  fclose(fh);
  return read;
}