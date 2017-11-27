    DEBUG ("exec plugin: exec_read_one: buffer = %s", buffer);

    parse_line (buffer);
  } /* while (fgets) */

  fclose (fh);
  pl->pid = 0;

  pthread_exit ((void *) 0);
  return (NULL);
} /* void *exec_read_one */

static int exec_read (void)
{
  program_list_t *pl;

  for (pl = pl_head; pl != NULL; pl = pl->next)
  {
    pthread_t t;
    pthread_attr_t attr;

    if (pl->pid != 0)
      continue;

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_create (&t, &attr, exec_read_one, (void *) pl);
  } /* for (pl) */

  return (0);
} /* int exec_read */

static int exec_shutdown (void)
{
  program_list_t *pl;
  program_list_t *next;

  pl = pl_head;
  while (pl != NULL)
