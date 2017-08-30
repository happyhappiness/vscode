{
  int i;
  linkname_t *lnp;

  if (t->options & TAR_NOOVERWRITE)
  {
    struct stat s;

#ifdef WIN32
    if (stat(realname, &s) == 0 || errno != ENOENT)
#else
    if (lstat(realname, &s) == 0 || errno != ENOENT)
#endif
    {
      errno = EEXIST;
      return -1;
    }
  }

  if (TH_ISDIR(t))
  {
    i = tar_extract_dir(t, realname);
    if (i == 1)
      i = 0;
  }
#ifndef _WIN32
  else if (TH_ISLNK(t))
    i = tar_extract_hardlink(t, realname);
  else if (TH_ISSYM(t))
    i = tar_extract_symlink(t, realname);
  else if (TH_ISCHR(t))
    i = tar_extract_chardev(t, realname);
  else if (TH_ISBLK(t))
    i = tar_extract_blockdev(t, realname);
  else if (TH_ISFIFO(t))
    i = tar_extract_fifo(t, realname);
#endif
  else /* if (TH_ISREG(t)) */
    i = tar_extract_regfile(t, realname);

  if (i != 0)
    return i;

  i = tar_set_file_perms(t, realname);
  if (i != 0)
    return i;

  lnp = (linkname_t *)calloc(1, sizeof(linkname_t));
  if (lnp == NULL)
    return -1;
  strlcpy(lnp->ln_save, th_get_pathname(t), sizeof(lnp->ln_save));
  strlcpy(lnp->ln_real, realname, sizeof(lnp->ln_real));
#ifdef DEBUG
  printf("tar_extract_file(): calling libtar_hash_add(): key=\"%s\", "
         "value=\"%s\"\n", th_get_pathname(t), realname);
#endif
  if (libtar_hash_add(t->h, lnp) != 0)
    return -1;

  return 0;
}