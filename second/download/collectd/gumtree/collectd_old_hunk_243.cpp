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
} /* void *exec_notification_one }}} */

static int exec_init (void) /* {{{ */
