SANITIZEcode msdosify(char **const sanitized, const char *file_name,
                      int flags)
{
  char dos_name[PATH_MAX];
  static const char illegal_chars_dos[] = ".+, ;=[]" /* illegal in DOS */
    "|<>/\\\":?*"; /* illegal in DOS & W95 */
  static const char *illegal_chars_w95 = &illegal_chars_dos[8];
  int idx, dot_idx;
  const char *s = file_name;
  char *d = dos_name;
  const char *const dlimit = dos_name + sizeof(dos_name) - 1;
  const char *illegal_aliens = illegal_chars_dos;
  size_t len = sizeof(illegal_chars_dos) - 1;

  if(!sanitized)
    return SANITIZE_ERR_BAD_ARGUMENT;

  *sanitized = NULL;

  if(!file_name)
    return SANITIZE_ERR_BAD_ARGUMENT;

  if(strlen(file_name) > PATH_MAX-1 &&
     (!(flags & SANITIZE_ALLOW_TRUNCATE) ||
      truncate_dryrun(file_name, PATH_MAX-1)))
    return SANITIZE_ERR_INVALID_PATH;

  /* Support for Windows 9X VFAT systems, when available. */
  if(_use_lfn(file_name)) {
    illegal_aliens = illegal_chars_w95;
    len -= (illegal_chars_w95 - illegal_chars_dos);
  }

  /* Get past the drive letter, if any. */
  if(s[0] >= 'A' && s[0] <= 'z' && s[1] == ':') {
    *d++ = *s++;
    *d = ((flags & (SANITIZE_ALLOW_COLONS|SANITIZE_ALLOW_PATH))) ? ':' : '_';
    ++d, ++s;
  }

  for(idx = 0, dot_idx = -1; *s && d < dlimit; s++, d++) {
    if(memchr(illegal_aliens, *s, len)) {

      if((flags & (SANITIZE_ALLOW_COLONS|SANITIZE_ALLOW_PATH)) && *s == ':')
        *d = ':';
      else if((flags & SANITIZE_ALLOW_PATH) && (*s == '/' || *s == '\\'))
        *d = *s;
      /* Dots are special: DOS doesn't allow them as the leading character,
         and a file name cannot have more than a single dot.  We leave the
         first non-leading dot alone, unless it comes too close to the
         beginning of the name: we want sh.lex.c to become sh_lex.c, not
         sh.lex-c.  */
      else if(*s == '.') {
        if((flags & SANITIZE_ALLOW_PATH) && idx == 0 &&
           (s[1] == '/' || s[1] == '\\' ||
            (s[1] == '.' && (s[2] == '/' || s[2] == '\\')))) {
          /* Copy "./" and "../" verbatim.  */
          *d++ = *s++;
          if(d == dlimit)
            break;
          if(*s == '.') {
            *d++ = *s++;
            if(d == dlimit)
              break;
          }
          *d = *s;
        }
        else if(idx == 0)
          *d = '_';
        else if(dot_idx >= 0) {
          if(dot_idx < 5) { /* 5 is a heuristic ad-hoc'ery */
            d[dot_idx - idx] = '_'; /* replace previous dot */
            *d = '.';
          }
          else
            *d = '-';
        }
        else
          *d = '.';

        if(*s == '.')
          dot_idx = idx;
      }
      else if(*s == '+' && s[1] == '+') {
        if(idx - 2 == dot_idx) { /* .c++, .h++ etc. */
          *d++ = 'x';
          if(d == dlimit)
            break;
          *d   = 'x';
        }
        else {
          /* libg++ etc.  */
          if(dlimit - d < 4) {
            *d++ = 'x';
            if(d == dlimit)
              break;
            *d   = 'x';
          }
          else {
            memcpy(d, "plus", 4);
            d += 3;
          }
        }
        s++;
        idx++;
      }
      else
        *d = '_';
    }
    else
      *d = *s;
    if(*s == '/' || *s == '\\') {
      idx = 0;
      dot_idx = -1;
    }
    else
      idx++;
  }
  *d = '\0';

  if(*s) {
    /* dos_name is truncated, check that truncation requirements are met,
       specifically truncating a filename suffixed by an alternate data stream
       or truncating the entire filename is not allowed. */
    if(!(flags & SANITIZE_ALLOW_TRUNCATE) || strpbrk(s, "\\/:") ||
       truncate_dryrun(dos_name, d - dos_name))
      return SANITIZE_ERR_INVALID_PATH;
  }

  *sanitized = strdup(dos_name);
  return (*sanitized ? SANITIZE_ERR_OK : SANITIZE_ERR_OUT_OF_MEMORY);
}