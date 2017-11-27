static int exec_notification (const notification_t *n)
{
  program_list_t *pl;
  program_list_and_notification_t *pln;

  for (pl = pl_head; pl != NULL; pl = pl->next)
  {
    pthread_t t;
    pthread_attr_t attr;

    /* Only execute `notification' style executables here. */
    if ((pl->flags & PL_NOTIF_ACTION) == 0)
      continue;

    /* Skip if a child is already running. */
    if (pl->pid != 0)
      continue;

    pln = (program_list_and_notification_t *) malloc (sizeof
	(program_list_and_notification_t));
    if (pln == NULL)
    {
      ERROR ("exec plugin: malloc failed.");
      continue;
    }

    pln->pl = pl;
    memcpy (&pln->n, n, sizeof (notification_t));

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_create (&t, &attr, exec_notification_one, (void *) pln);
  } /* for (pl) */

  return (0);
}