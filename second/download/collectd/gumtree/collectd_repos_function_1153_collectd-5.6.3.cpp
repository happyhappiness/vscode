static int drbd_read(void) {
  FILE *fh;
  char buffer[256];

  long int resource = -1;
  char *fields[16];
  int fields_num = 0;

  fh = fopen(drbd_stats, "r");
  if (fh == NULL) {
    WARNING("drbd plugin: Unable to open %s", drbd_stats);
    return (EINVAL);
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    fields_num = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

    /* ignore headers (first two iterations) */
    if ((strcmp(fields[0], "version:") == 0) ||
        (strcmp(fields[0], "srcversion:") == 0) ||
        (strcmp(fields[0], "GIT-hash:") == 0)) {
      continue;
    }

    if (isdigit(fields[0][0])) {
      /* parse the resource line, next loop iteration
         will submit values for this resource */
      resource = strtol(fields[0], NULL, 10);
    } else {
      /* handle stats data for the resource defined in the
         previous iteration */
      drbd_submit_fields(resource, fields, fields_num);
    }
  } /* while (fgets) */

  fclose(fh);
  return (0);
}