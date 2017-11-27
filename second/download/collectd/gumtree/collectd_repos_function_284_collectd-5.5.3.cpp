static int ping_init (void) /* {{{ */
{
  if (hostlist_head == NULL)
  {
    NOTICE ("ping plugin: No hosts have been configured.");
    return (-1);
  }

  if (ping_timeout > ping_interval)
  {
    ping_timeout = 0.9 * ping_interval;
    WARNING ("ping plugin: Timeout is greater than interval. "
        "Will use a timeout of %gs.", ping_timeout);
  }

  return (start_thread ());
}