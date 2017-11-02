static char *rename_if_dos_device_name (char *file_name)
{
  /* We could have a file whose name is a device on MS-DOS.  Trying to
   * retrieve such a file would fail at best and wedge us at worst.  We need
   * to rename such files. */
  char *base;
  struct_stat st_buf;
  char fname[PATH_MAX];

  strncpy(fname, file_name, PATH_MAX-1);
  fname[PATH_MAX-1] = '\0';
  base = basename(fname);
  if(((stat(base, &st_buf)) == 0) && (S_ISCHR(st_buf.st_mode))) {
    size_t blen = strlen(base);

    if(strlen(fname) >= PATH_MAX-1) {
      /* Make room for the '_' */
      blen--;
      base[blen] = '\0';
    }
    /* Prepend a '_'.  */
    memmove(base + 1, base, blen + 1);
    base[0] = '_';
    strcpy(file_name, fname);
  }
  return file_name;
}