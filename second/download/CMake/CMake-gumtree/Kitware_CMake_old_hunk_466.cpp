  fprintf(out, "%-*s ", (int)u_width, p);
  /* Use gname if it's present, else gid. */
  p = archive_entry_gname(entry);
  if (p != NULL && p[0] != '\0') {
    fprintf(out, "%s", p);
    w = strlen(p);
  } else {
