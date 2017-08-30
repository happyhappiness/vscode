  fprintf(out, "%s %d ",

          archive_entry_strmode(entry),

          archive_entry_nlink(entry));

  

  /* Use uname if it's present, else uid. */

  p = archive_entry_uname(entry);

  if ((p == NULL) || (*p == '\0'))

