static int
chrony_init_seq(void)
{
  /* Initialize the sequence number generator from /dev/urandom */
  /* Fallbacks: /dev/random and time(NULL) */

  int fh;

  /* Try urandom */
  fh = open(URAND_DEVICE_PATH, O_RDONLY);
  if (fh >= 0)
  {
    ssize_t rc = read(fh, &g_chrony_rand, sizeof(g_chrony_rand));
    if (rc != sizeof(g_chrony_rand))
    {
      ERROR(PLUGIN_NAME ": Reading from random source \'%s\'failed: %s (%d)",
            URAND_DEVICE_PATH, strerror(errno), errno);
      close(fh);
      return CHRONY_RC_FAIL;
    }
    close(fh);
    DEBUG(PLUGIN_NAME ": Seeding RNG from " URAND_DEVICE_PATH);
  }
  else
  {
    if (errno == ENOENT)
    {
      /* URAND_DEVICE_PATH device not found. Try RAND_DEVICE_PATH as fall-back */
      fh = open(RAND_DEVICE_PATH, O_RDONLY);
      if (fh >= 0)
      {
        ssize_t rc = read(fh, &g_chrony_rand, sizeof(g_chrony_rand));
        if (rc != sizeof(g_chrony_rand))
        {
          ERROR(PLUGIN_NAME
                ": Reading from random source \'%s\'failed: %s (%d)",
                RAND_DEVICE_PATH, strerror(errno), errno);
          close(fh);
          return CHRONY_RC_FAIL;
        }
        close(fh);
        DEBUG(PLUGIN_NAME ": Seeding RNG from " RAND_DEVICE_PATH);
      }
      else
      {
        /* Error opening RAND_DEVICE_PATH. Try time(NULL) as fall-back */
        DEBUG(PLUGIN_NAME ": Seeding RNG from time(NULL)");
        g_chrony_rand = time(NULL) ^ getpid();
      }
    }
    else
    {
      ERROR(PLUGIN_NAME ": Opening random source \'%s\' failed: %s (%d)",
            URAND_DEVICE_PATH, strerror(errno), errno);
      return CHRONY_RC_FAIL;
    }
  }

  return CHRONY_RC_OK;
}