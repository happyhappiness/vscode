static int olsrd_read(void) /* {{{ */
{
  FILE *fh;
  char buffer[1024];
  size_t buffer_len;

  fh = olsrd_connect();
  if (fh == NULL)
    return -1;

  fputs("\r\n", fh);
  fflush(fh);

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    buffer_len = strchomp(buffer);
    if (buffer_len == 0)
      continue;

    if (strcmp("Table: Links", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_links);
    else if (strcmp("Table: Neighbors", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_ignore);
    else if (strcmp("Table: Topology", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_topology);
    else if (strcmp("Table: HNA", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_ignore);
    else if (strcmp("Table: MID", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_ignore);
    else if (strcmp("Table: Routes", buffer) == 0)
      olsrd_read_table(fh, olsrd_cb_routes);
    else if ((strcmp("HTTP/1.0 200 OK", buffer) == 0) ||
             (strcmp("Content-type: text/plain", buffer) == 0)) {
      /* ignore */
    } else {
      DEBUG("olsrd plugin: Unable to handle line: %s", buffer);
    }
  } /* while (fgets) */

  fclose(fh);

  return 0;
}