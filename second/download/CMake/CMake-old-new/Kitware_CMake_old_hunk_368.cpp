
  /* Use uname if it's present, else uid. */
  p = archive_entry_uname(entry);
  if ((p == NULL) || (*p == '\0')) {
    sprintf(tmp, "%lu ", (unsigned long)archive_entry_uid(entry));
    p = tmp;
  }
