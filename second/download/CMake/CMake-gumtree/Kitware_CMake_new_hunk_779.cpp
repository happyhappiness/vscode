    }

  strftime(tmp, sizeof(tmp), fmt, localtime(&tim));

  fprintf(out, " %s ", tmp);

  fprintf(out, "%s", cm_archive_entry_pathname(entry).c_str());



  /* Extra information for links. */

  if (archive_entry_hardlink(entry)) /* Hard link */

