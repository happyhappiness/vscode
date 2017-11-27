static int
chrony_connect(void)
{
  /* Connects to the chrony daemon */
  /* Returns 0 on success, !0 on error (check errno) */
  int socket;

  if (g_chrony_host == NULL)
  {
    g_chrony_host = strdup(CHRONY_DEFAULT_HOST);
    if (g_chrony_host == NULL)
    {
      ERROR(PLUGIN_NAME ": Error duplicating chrony host name");
      return CHRONY_RC_FAIL;
    }
  }
  if (g_chrony_port == NULL)
  {
    g_chrony_port = strdup(CHRONY_DEFAULT_PORT);
    if (g_chrony_port == NULL)
    {
      ERROR(PLUGIN_NAME ": Error duplicating chrony port string");
      return CHRONY_RC_FAIL;
    }
  }
  if (g_chrony_timeout < 0)
  {
    g_chrony_timeout = CHRONY_DEFAULT_TIMEOUT;
    assert(g_chrony_timeout >= 0);
  }

  DEBUG(PLUGIN_NAME ": Connecting to %s:%s", g_chrony_host, g_chrony_port);
  socket = connect_client(g_chrony_host, g_chrony_port, AF_UNSPEC, SOCK_DGRAM);
  if (socket < 0)
  {
    ERROR(PLUGIN_NAME ": Error connecting to daemon. Errno = %d", errno);
    return CHRONY_RC_FAIL;
  }
  DEBUG(PLUGIN_NAME ": Connected");
  g_chrony_socket = socket;

  if (chrony_set_timeout())
  {
    ERROR(PLUGIN_NAME ": Error setting timeout to %llds. Errno = %d",
          (long long)g_chrony_timeout, errno);
    return CHRONY_RC_FAIL;
  }
  return CHRONY_RC_OK;
}