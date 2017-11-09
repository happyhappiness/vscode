int mx_unlock_file (const char *path, int fd, int dot)
{
#ifdef USE_FCNTL
  struct flock unlockit = { F_UNLCK, 0, 0, 0, 0 };

  memset (&unlockit, 0, sizeof (struct flock));
  unlockit.l_type = F_UNLCK;
  unlockit.l_whence = SEEK_SET;
  fcntl (fd, F_SETLK, &unlockit);
#endif

#ifdef USE_FLOCK
  flock (fd, LOCK_UN);
#endif

#ifdef USE_DOTLOCK
  if (dot)
    undotlock_file (path, fd);
#endif
  
  return 0;
}