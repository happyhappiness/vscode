    gs_width = w+strlen(tmp)+1;

    }

  fprintf(out, "%*s", (int)(gs_width - w), tmp);

  

  /* Format the time using 'ls -l' conventions. */

  tim = archive_entry_mtime(entry);

#define HALF_YEAR (time_t)365 * 86400 / 2

