  fputs ("\r\n", fh);
  fflush (fh);

  while (fgets (buffer, sizeof (buffer), fh) != NULL)
  {
    buffer_len = strchomp (buffer);
    if (buffer_len == 0)
      continue;

    if (strcmp ("Table: Links", buffer) == 0)
      olsrd_read_table (fh, olsrd_cb_links);
    else if (strcmp ("Table: Neighbors", buffer) == 0)
      olsrd_read_table (fh, olsrd_cb_ignore);
    else if (strcmp ("Table: Topology", buffer) == 0)
      olsrd_read_table (fh, olsrd_cb_topology);
