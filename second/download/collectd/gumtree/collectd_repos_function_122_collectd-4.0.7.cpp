static void *exec_read_one (void *arg)
{
  program_list_t *pl = (program_list_t *) arg;
  int fd;
  FILE *fh;
  char buffer[1024];

  fd = fork_child (pl);
  if (fd < 0)
    pthread_exit ((void *) 1);

  assert (pl->pid != 0);

  fh = fdopen (fd, "r");
  if (fh == NULL)
  {
    char errbuf[1024];
    ERROR ("exec plugin: fdopen (%i) failed: %s", fd,
	sstrerror (errno, errbuf, sizeof (errbuf)));
    kill (pl->pid, SIGTERM);
    close (fd);
    pthread_exit ((void *) 1);
  }

  while (fgets (buffer, sizeof (buffer), fh) != NULL)
  {
    int len;

    len = strlen (buffer);

    /* Remove newline from end. */
    while ((len > 0) && ((buffer[len - 1] == '\n')
	  || (buffer[len - 1] == '\r')))
      buffer[--len] = '\0';

    DEBUG ("exec plugin: exec_read_one: buffer = %s", buffer);

    parse_line (buffer);
  } /* while (fgets) */

  fclose (fh);
  pl->pid = 0;

  pthread_exit ((void *) 0);
  return (NULL);
}