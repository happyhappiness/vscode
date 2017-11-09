SANITIZEcode rename_if_reserved_dos_device_name(char **const sanitized,
                                                const char *file_name,
                                                int flags)
{
  /* We could have a file whose name is a device on MS-DOS.  Trying to
   * retrieve such a file would fail at best and wedge us at worst.  We need
   * to rename such files. */
  char *p, *base;
  char fname[PATH_MAX];
#ifdef MSDOS
  struct_stat st_buf;
#endif

  if(!sanitized)
    return SANITIZE_ERR_BAD_ARGUMENT;

  *sanitized = NULL;

  if(!file_name)
    return SANITIZE_ERR_BAD_ARGUMENT;

  /* Ignore UNC prefixed paths, they are allowed to contain a reserved name. */
#ifndef MSDOS
  if((flags & SANITIZE_ALLOW_PATH) &&
     file_name[0] == '\\' && file_name[1] == '\\') {
    size_t len = strlen(file_name);
    *sanitized = malloc(len + 1);
    if(!*sanitized)
      return SANITIZE_ERR_OUT_OF_MEMORY;
    strncpy(*sanitized, file_name, len + 1);
    return SANITIZE_ERR_OK;
  }
#endif

  if(strlen(file_name) > PATH_MAX-1 &&
     (!(flags & SANITIZE_ALLOW_TRUNCATE) ||
      truncate_dryrun(file_name, PATH_MAX-1)))
    return SANITIZE_ERR_INVALID_PATH;

  strncpy(fname, file_name, PATH_MAX-1);
  fname[PATH_MAX-1] = '\0';
  base = basename(fname);

  /* Rename reserved device names that are known to be accessible without \\.\
     Examples: CON => _CON, CON.EXT => CON_EXT, CON:ADS => CON_ADS
     https://support.microsoft.com/en-us/kb/74496
     https://msdn.microsoft.com/en-us/library/windows/desktop/aa365247.aspx
     */
  for(p = fname; p; p = (p == fname && fname != base ? base : NULL)) {
    size_t p_len;
    int x = (curl_strnequal(p, "CON", 3) ||
             curl_strnequal(p, "PRN", 3) ||
             curl_strnequal(p, "AUX", 3) ||
             curl_strnequal(p, "NUL", 3)) ? 3 :
            (curl_strnequal(p, "CLOCK$", 6)) ? 6 :
            (curl_strnequal(p, "COM", 3) || curl_strnequal(p, "LPT", 3)) ?
              (('1' <= p[3] && p[3] <= '9') ? 4 : 3) : 0;

    if(!x)
      continue;

    /* the devices may be accessible with an extension or ADS, for
       example CON.AIR and 'CON . AIR' and CON:AIR access console */

    for(; p[x] == ' '; ++x)
      ;

    if(p[x] == '.') {
      p[x] = '_';
      continue;
    }
    else if(p[x] == ':') {
      if(!(flags & (SANITIZE_ALLOW_COLONS|SANITIZE_ALLOW_PATH))) {
        p[x] = '_';
        continue;
      }
      ++x;
    }
    else if(p[x]) /* no match */
      continue;

    /* p points to 'CON' or 'CON ' or 'CON:', etc */
    p_len = strlen(p);

    /* Prepend a '_' */
    if(strlen(fname) == PATH_MAX-1) {
      --p_len;
      if(!(flags & SANITIZE_ALLOW_TRUNCATE) || truncate_dryrun(p, p_len))
        return SANITIZE_ERR_INVALID_PATH;
      p[p_len] = '\0';
    }
    memmove(p + 1, p, p_len + 1);
    p[0] = '_';
    ++p_len;

    /* if fname was just modified then the basename pointer must be updated */
    if(p == fname)
      base = basename(fname);
  }

  /* This is the legacy portion from rename_if_dos_device_name that checks for
     reserved device names. It only works on MSDOS. On Windows XP the stat
     check errors with EINVAL if the device name is reserved. On Windows
     Vista/7/8 it sets mode S_IFREG (regular file or device). According to MSDN
     stat doc the latter behavior is correct, but that doesn't help us identify
     whether it's a reserved device name and not a regular file name. */
#ifdef MSDOS
  if(base && ((stat(base, &st_buf)) == 0) && (S_ISCHR(st_buf.st_mode))) {
    /* Prepend a '_' */
    size_t blen = strlen(base);
    if(blen) {
      if(strlen(fname) == PATH_MAX-1) {
        --blen;
        if(!(flags & SANITIZE_ALLOW_TRUNCATE) || truncate_dryrun(base, blen))
          return SANITIZE_ERR_INVALID_PATH;
        base[blen] = '\0';
      }
      memmove(base + 1, base, blen + 1);
      base[0] = '_';
      ++blen;
    }
  }
#endif

  *sanitized = strdup(fname);
  return (*sanitized ? SANITIZE_ERR_OK : SANITIZE_ERR_OUT_OF_MEMORY);
}