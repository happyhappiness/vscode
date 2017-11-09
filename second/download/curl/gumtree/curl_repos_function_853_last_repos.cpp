SANITIZEcode sanitize_file_name(char **const sanitized, const char *file_name,
                                int flags)
{
  char *p, *target;
  size_t len;
  SANITIZEcode sc;
  size_t max_sanitized_len;

  if(!sanitized)
    return SANITIZE_ERR_BAD_ARGUMENT;

  *sanitized = NULL;

  if(!file_name)
    return SANITIZE_ERR_BAD_ARGUMENT;

  if((flags & SANITIZE_ALLOW_PATH)) {
#ifndef MSDOS
    if(file_name[0] == '\\' && file_name[1] == '\\')
      /* UNC prefixed path \\ (eg \\?\C:\foo) */
      max_sanitized_len = 32767-1;
    else
#endif
      max_sanitized_len = PATH_MAX-1;
  }
  else
    /* The maximum length of a filename.
       FILENAME_MAX is often the same as PATH_MAX, in other words it is 260 and
       does not discount the path information therefore we shouldn't use it. */
    max_sanitized_len = (PATH_MAX-1 > 255) ? 255 : PATH_MAX-1;

  len = strlen(file_name);
  if(len > max_sanitized_len) {
    if(!(flags & SANITIZE_ALLOW_TRUNCATE) ||
       truncate_dryrun(file_name, max_sanitized_len))
      return SANITIZE_ERR_INVALID_PATH;

    len = max_sanitized_len;
  }

  target = malloc(len + 1);
  if(!target)
    return SANITIZE_ERR_OUT_OF_MEMORY;

  strncpy(target, file_name, len);
  target[len] = '\0';

#ifndef MSDOS
  if((flags & SANITIZE_ALLOW_PATH) && !strncmp(target, "\\\\?\\", 4))
    /* Skip the literal path prefix \\?\ */
    p = target + 4;
  else
#endif
    p = target;

  /* replace control characters and other banned characters */
  for(; *p; ++p) {
    const char *banned;

    if((1 <= *p && *p <= 31) ||
       (!(flags & (SANITIZE_ALLOW_COLONS|SANITIZE_ALLOW_PATH)) && *p == ':') ||
       (!(flags & SANITIZE_ALLOW_PATH) && (*p == '/' || *p == '\\'))) {
      *p = '_';
      continue;
    }

    for(banned = "|<>\"?*"; *banned; ++banned) {
      if(*p == *banned) {
        *p = '_';
        break;
      }
    }
  }

  /* remove trailing spaces and periods if not allowing paths */
  if(!(flags & SANITIZE_ALLOW_PATH) && len) {
    char *clip = NULL;

    p = &target[len];
    do {
      --p;
      if(*p != ' ' && *p != '.')
        break;
      clip = p;
    } while(p != target);

    if(clip) {
      *clip = '\0';
      len = clip - target;
    }
  }

#ifdef MSDOS
  sc = msdosify(&p, target, flags);
  free(target);
  if(sc)
    return sc;
  target = p;
  len = strlen(target);

  if(len > max_sanitized_len) {
    free(target);
    return SANITIZE_ERR_INVALID_PATH;
  }
#endif

  if(!(flags & SANITIZE_ALLOW_RESERVED)) {
    sc = rename_if_reserved_dos_device_name(&p, target, flags);
    free(target);
    if(sc)
      return sc;
    target = p;
    len = strlen(target);

    if(len > max_sanitized_len) {
      free(target);
      return SANITIZE_ERR_INVALID_PATH;
    }
  }

  *sanitized = target;
  return SANITIZE_ERR_OK;
}