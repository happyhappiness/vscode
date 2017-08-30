  strftime(tmp, sizeof(tmp), fmt, localtime(&tim));

  fprintf(out, " %s ", tmp);

  fprintf(out, "%s", archive_entry_pathname(entry));



  /* Extra information for links. */

  if (archive_entry_hardlink(entry)) /* Hard link */

    {

