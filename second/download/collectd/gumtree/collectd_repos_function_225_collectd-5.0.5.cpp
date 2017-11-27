static int exec_read (void) /* {{{ */
{
  program_list_t *pl;

  for (pl = pl_head; pl != NULL; pl = pl->next)
  {
    pthread_t t;
    pthread_attr_t attr;

    /* Only execute `normal' style executables here. */
    if ((pl->flags & PL_NORMAL) == 0)
      continue;

    pthread_mutex_lock (&pl_lock);
    /* Skip if a child is already running. */
    if ((pl->flags & PL_RUNNING) != 0)
    {
      pthread_mutex_unlock (&pl_lock);
      continue;
    }
    pl->flags |= PL_RUNNING;
    pthread_mutex_unlock (&pl_lock);

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_create (&t, &attr, exec_read_one, (void *) pl);
    pthread_attr_destroy (&attr);
  } /* for (pl) */

  return (0);
}