static int ssl_init (void)
{
  char path[_POSIX_PATH_MAX];
  static unsigned char init_complete = 0;

  if (init_complete)
    return 0;

  if (! HAVE_ENTROPY())
  {
    /* load entropy from files */
    add_entropy (SslEntropyFile);
    add_entropy (RAND_file_name (path, sizeof (path)));

    /* load entropy from egd sockets */
#ifdef HAVE_RAND_EGD
    add_entropy (getenv ("EGDSOCKET"));
    snprintf (path, sizeof(path), "%s/.entropy", NONULL(Homedir));
    add_entropy (path);
    add_entropy ("/tmp/entropy");
#endif

    /* shuffle $RANDFILE (or ~/.rnd if unset) */
    RAND_write_file (RAND_file_name (path, sizeof (path)));
    mutt_clear_error ();
    if (! HAVE_ENTROPY())
    {
      mutt_error (_("Failed to find enough entropy on your system"));
      mutt_sleep (2);
      return -1;
    }
  }

  /* I don't think you can do this just before reading the error. The call
   * itself might clobber the last SSL error. */
  SSL_load_error_strings();
  SSL_library_init();
  init_complete = 1;
  return 0;
}