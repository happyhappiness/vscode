{
  mode_t mode;
  size_t size;
  uid_t uid;
  gid_t gid;
  int fdout;
  int i, k;
  char buf[T_BLOCKSIZE];
  char *filename;

#ifdef DEBUG
  printf("==> tar_extract_regfile(t=0x%lx, realname=\"%s\")\n", t,
         realname);
#endif

  if (!TH_ISREG(t))
  {
    errno = EINVAL;
    return -1;
  }

  filename = (realname ? realname : th_get_pathname(t));
  mode = th_get_mode(t);
  size = th_get_size(t);
  uid = th_get_uid(t);
  gid = th_get_gid(t);

  /* Make a copy of the string because dirname and mkdirhier may modify the
   * string */
  strncpy(buf, filename, sizeof(buf)-1);
  buf[sizeof(buf)-1] = 0;

  if (mkdirhier(dirname(buf)) == -1)
    {
    return -1;
    }

#ifdef DEBUG
  printf("  ==> extracting: %s (mode %04o, uid %d, gid %d, %d bytes)\n",
         filename, mode, uid, gid, size);
#endif
  fdout = open(filename, O_WRONLY | O_CREAT | O_TRUNC
#ifdef O_BINARY
         | O_BINARY
#endif
        , 0666);
  if (fdout == -1)
  {
#ifdef DEBUG
    perror("open()");
#endif
    return -1;
  }

#if 0
  /* change the owner.  (will only work if run as root) */
  if (fchown(fdout, uid, gid) == -1 && errno != EPERM)
  {
#ifdef DEBUG
    perror("fchown()");
#endif
    return -1;
  }

  /* make sure the mode isn't inheritted from a file we're overwriting */
  if (fchmod(fdout, mode & 07777) == -1)
  {
#ifdef DEBUG
    perror("fchmod()");
#endif
    return -1;
  }
#endif

  /* extract the file */
  for (i = size; i > 0; i -= T_BLOCKSIZE)
  {
    k = tar_block_read(t, buf);
    if (k != T_BLOCKSIZE)
    {
      if (k != -1)
        errno = EINVAL;
      return -1;
    }

    /* write block to output file */
    if (write(fdout, buf,
        ((i > T_BLOCKSIZE) ? T_BLOCKSIZE : i)) == -1)
      return -1;
  }

  /* close output file */
  if (close(fdout) == -1)
    return -1;

#ifdef DEBUG
  printf("### done extracting %s\n", filename);
#endif

  (void)filename;
  (void)gid;
  (void)uid;
  (void)mode;

  return 0;
}