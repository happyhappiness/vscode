static int add_entropy (const char *file)
{
  struct stat st;
  int n = -1;

  if (!file) return 0;

  if (stat (file, &st) == -1)
    return errno == ENOENT ? 0 : -1;

  mutt_message (_("Filling entropy pool: %s...\n"),
		file);

  /* check that the file permissions are secure */
  if (st.st_uid != getuid () ||
      ((st.st_mode & (S_IWGRP | S_IRGRP)) != 0) ||
      ((st.st_mode & (S_IWOTH | S_IROTH)) != 0))
  {
    mutt_error (_("%s has insecure permissions!"), file);
    mutt_sleep (2);
    return -1;
  }

#ifdef HAVE_RAND_EGD
  n = RAND_egd (file);
#endif
  if (n <= 0)
    n = RAND_load_file (file, -1);

#ifndef HAVE_RAND_STATUS
  if (n > 0) entropy_byte_count += n;
#endif
  return n;
}