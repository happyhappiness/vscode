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
