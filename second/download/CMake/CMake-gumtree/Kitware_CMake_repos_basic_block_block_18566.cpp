{
  int    evp_rc, i;
  char   *p;
  char   filename[PATH_MAX]; /* To be used when handling directories */

  p = buf;
  *events = 0;

  /* Clean the filename buffer*/
  for(i = 0; i < PATH_MAX; i++) {
    filename[i] = 0;
  }
  i = 0;

  /* Check for BUF_WRAP */
  if (strncmp(buf, "BUF_WRAP", strlen("BUF_WRAP")) == 0) {
    assert(0 && "Buffer wrap detected, Some event occurrences lost!");
    return 0;
  }

  /* Since we are using the default buffer size (4K), and have specified
   * INFO_LVL=1, we won't see any EVENT_OVERFLOW conditions.  Applications
   * should check for this keyword if they are using an INFO_LVL of 2 or
   * higher, and have a buffer size of <= 4K
   */

  /* Skip to RC_FROM_EVPROD */
  if (uv__skip_lines(&p, 9) != 9)
    return -1;

  if (sscanf(p, "RC_FROM_EVPROD=%d\nEND_EVENT_DATA", &evp_rc) == 1) {
    if (uv__path_is_a_directory(handle->path) == 0) { /* Directory */
      if (evp_rc == AHAFS_MODDIR_UNMOUNT || evp_rc == AHAFS_MODDIR_REMOVE_SELF) {
        /* The directory is no longer available for monitoring */
        *events = UV_RENAME;
        handle->dir_filename = NULL;
      } else {
        /* A file was added/removed inside the directory */
        *events = UV_CHANGE;

        /* Get the EVPROD_INFO */
        if (uv__skip_lines(&p, 1) != 1)
          return -1;

        /* Scan out the name of the file that triggered the event*/
        if (sscanf(p, "BEGIN_EVPROD_INFO\n%sEND_EVPROD_INFO", filename) == 1) {
          handle->dir_filename = uv__strdup((const char*)&filename);
        } else
          return -1;
        }
    } else { /* Regular File */
      if (evp_rc == AHAFS_MODFILE_RENAME)
        *events = UV_RENAME;
      else
        *events = UV_CHANGE;
    }
  }
  else
    return -1;

  return 0;
}