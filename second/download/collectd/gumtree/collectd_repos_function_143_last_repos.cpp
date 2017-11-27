static void *exec_notification_one(void *arg) /* {{{ */
{
  program_list_t *pl = ((program_list_and_notification_t *)arg)->pl;
  notification_t *n = &((program_list_and_notification_t *)arg)->n;
  int fd;
  FILE *fh;
  int pid;
  int status;
  const char *severity;

  pid = fork_child(pl, &fd, NULL, NULL);
  if (pid < 0) {
    sfree(arg);
    pthread_exit((void *)1);
  }

  fh = fdopen(fd, "w");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("exec plugin: fdopen (%i) failed: %s", fd,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    kill(pid, SIGTERM);
    close(fd);
    sfree(arg);
    pthread_exit((void *)1);
  }

  severity = "FAILURE";
  if (n->severity == NOTIF_WARNING)
    severity = "WARNING";
  else if (n->severity == NOTIF_OKAY)
    severity = "OKAY";

  fprintf(fh, "Severity: %s\n"
              "Time: %.3f\n",
          severity, CDTIME_T_TO_DOUBLE(n->time));

  /* Print the optional fields */
  if (strlen(n->host) > 0)
    fprintf(fh, "Host: %s\n", n->host);
  if (strlen(n->plugin) > 0)
    fprintf(fh, "Plugin: %s\n", n->plugin);
  if (strlen(n->plugin_instance) > 0)
    fprintf(fh, "PluginInstance: %s\n", n->plugin_instance);
  if (strlen(n->type) > 0)
    fprintf(fh, "Type: %s\n", n->type);
  if (strlen(n->type_instance) > 0)
    fprintf(fh, "TypeInstance: %s\n", n->type_instance);

  for (notification_meta_t *meta = n->meta; meta != NULL; meta = meta->next) {
    if (meta->type == NM_TYPE_STRING)
      fprintf(fh, "%s: %s\n", meta->name, meta->nm_value.nm_string);
    else if (meta->type == NM_TYPE_SIGNED_INT)
      fprintf(fh, "%s: %" PRIi64 "\n", meta->name,
              meta->nm_value.nm_signed_int);
    else if (meta->type == NM_TYPE_UNSIGNED_INT)
      fprintf(fh, "%s: %" PRIu64 "\n", meta->name,
              meta->nm_value.nm_unsigned_int);
    else if (meta->type == NM_TYPE_DOUBLE)
      fprintf(fh, "%s: %e\n", meta->name, meta->nm_value.nm_double);
    else if (meta->type == NM_TYPE_BOOLEAN)
      fprintf(fh, "%s: %s\n", meta->name,
              meta->nm_value.nm_boolean ? "true" : "false");
  }

  fprintf(fh, "\n%s\n", n->message);

  fflush(fh);
  fclose(fh);

  waitpid(pid, &status, 0);

  DEBUG("exec plugin: Child %i exited with status %i.", pid, status);

  if (n->meta != NULL)
    plugin_notification_meta_free(n->meta);
  n->meta = NULL;
  sfree(arg);
  pthread_exit((void *)0);
  return NULL;
}