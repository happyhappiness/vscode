    {

    fprintf(out, "%s", p);

    w = strlen(p);

    }

  else

    {

    sprintf(tmp, "%lu",

            (unsigned long)archive_entry_gid(entry));

    w = strlen(tmp);

    fprintf(out, "%s", tmp);

    }



  /*

   * Print device number or file size, right-aligned so as to make

   * total width of group and devnum/filesize fields be gs_width.

   * If gs_width is too small, grow it.

   */

  if (archive_entry_filetype(entry) == AE_IFCHR

      || archive_entry_filetype(entry) == AE_IFBLK)

    {

    sprintf(tmp, "%lu,%lu",

            (unsigned long)archive_entry_rdevmajor(entry),

            (unsigned long)archive_entry_rdevminor(entry));

    }

  else

    {

    /*

     * Note the use of platform-dependent macros to format

