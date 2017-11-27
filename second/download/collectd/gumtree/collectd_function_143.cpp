static void *exec_notification_one (void *arg) /* {{{ */
{
  program_list_t *pl = ((program_list_and_notification_t *) arg)->pl;
  const notification_t *n = &((program_list_and_notification_t *) arg)->n;
  int fd;
  FILE *fh;
  int pid;
  int status;
  const char *severity;

  pid = fork_child (pl, &fd, NULL);
  if (pid < 0) {
    sfree (arg);
    pthread_exit ((void *) 1);
  }

  fh = fdopen (fd, "w");
  if (fh == NULL)
  {
    char errbuf[1024];
    ERROR ("exec plugin: fdopen (%i) failed: %s", fd,
	sstrerror (errno, errbuf, sizeof (errbuf)));
    kill (pl->pid, SIGTERM);
    pl->pid = 0;
    close (fd);
    sfree (arg);
    pthread_exit ((void *) 1);
  }

  severity = "FAILURE";
  if (n->severity == NOTIF_WARNING)
    severity = "WARNING";
  else if (n->severity == NOTIF_OKAY)
    severity = "OKAY";

  fprintf (fh,
      "Severity: %s\n"
      "Time: %u\n",
      severity, (unsigned int) n->time);

  /* Print the optional fields */
  if (strlen (n->host) > 0)
    fprintf (fh, "Host: %s\n", n->host);
  if (strlen (n->plugin) > 0)
    fprintf (fh, "Plugin: %s\n", n->plugin);
  if (strlen (n->plugin_instance) > 0)
    fprintf (fh, "PluginInstance: %s\n", n->plugin_instance);
  if (strlen (n->type) > 0)
    fprintf (fh, "Type: %s\n", n->type);
  if (strlen (n->type_instance) > 0)
    fprintf (fh, "TypeInstance: %s\n", n->type_instance);

  fprintf (fh, "\n%s\n", n->message);

  fflush (fh);
  fclose (fh);

  waitpid (pid, &status, 0);

  DEBUG ("exec plugin: Child %i exited with status %i.",
      pid, status);

  sfree (arg);
  pthread_exit ((void *) 0);
  return (NULL);
}