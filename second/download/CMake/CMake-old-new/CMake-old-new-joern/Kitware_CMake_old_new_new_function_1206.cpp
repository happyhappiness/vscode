int
tar_extract_dir(TAR *t, char *realname)
{
  mode_t mode;
  char *filename;
  char buf[T_BLOCKSIZE];
  char *pathname = 0;
  size_t len = 0;

  if (!TH_ISDIR(t))
  {
    errno = EINVAL;
    return -1;
  }

  if (realname)
    {
    filename = realname;
    }
  else
    {
    pathname = th_get_pathname(t);
    filename = pathname;
    }
  mode = th_get_mode(t);

  /* Make a copy of the string because dirname and mkdirhier may modify the
   * string */
  strncpy(buf, filename, sizeof(buf)-1);
  buf[sizeof(buf)-1] = 0;

  if (mkdirhier(dirname(buf)) == -1)
    {
    if (pathname)
      {
      free(pathname);
      }
    return -1;
    }

    /* Strip trailing '/'...it confuses some Unixes (and BeOS)... */
    strncpy(buf, filename, sizeof(buf)-1);
    buf[sizeof(buf)-1] = 0;
    len = strlen(buf);
    if ((len > 0) && (buf[len-1] == '/'))
      {
      buf[len-1] = '\0';
      }

#ifdef DEBUG
  printf("  ==> extracting: %s (mode %04o, directory)\n", filename,
         mode);
#endif
#ifdef WIN32
  if (mkdir(buf) == -1)
#else
  if (mkdir(buf, mode & 07777) == -1)
#endif
  {
#ifdef __BORLANDC__
  /* There is a bug in the Borland Run time library which makes MKDIR
     return EACCES when it should return EEXIST
     if it is some other error besides directory exists
     then return false */
    if ( errno == EACCES) 
    {
      errno = EEXIST;
    }
#endif      
    if (errno == EEXIST)
    {
      if (chmod(filename, mode & 07777) == -1)
      {
#ifdef DEBUG
        perror("chmod()");
#endif
        if (pathname)
          {
          free(pathname);
          }
        return -1;
      }
      else
      {
#ifdef DEBUG
        puts("  *** using existing directory");
#endif
        if (pathname)
          {
          free(pathname);
          }
        return 1;
      }
    }
    else
    {
#ifdef DEBUG
      perror("mkdir()");
#endif
      if (pathname)
        {
        free(pathname);
        }
      return -1;
    }
  }

  if (pathname)
    {
    free(pathname);
    }
  return 0;
}