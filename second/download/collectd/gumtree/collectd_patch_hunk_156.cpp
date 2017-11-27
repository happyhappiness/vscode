     DEBUG ("exec plugin: exec_read_one: buffer = %s", buffer);
 
     parse_line (buffer);
   } /* while (fgets) */
 
   fclose (fh);
+
+  if (waitpid (pl->pid, &status, 0) > 0)
+    pl->status = status;
+
+  DEBUG ("exec plugin: Child %i exited with status %i.",
+      (int) pl->pid, pl->status);
+
   pl->pid = 0;
 
+  pthread_mutex_lock (&pl_lock);
+  pl->flags &= ~PL_RUNNING;
+  pthread_mutex_unlock (&pl_lock);
+
   pthread_exit ((void *) 0);
   return (NULL);
-} /* void *exec_read_one */
+} /* void *exec_read_one }}} */
 
-static int exec_read (void)
+static void *exec_notification_one (void *arg) /* {{{ */
+{
+  program_list_t *pl = ((program_list_and_notification_t *) arg)->pl;
+  const notification_t *n = &((program_list_and_notification_t *) arg)->n;
+  int fd;
+  FILE *fh;
+  int pid;
+  int status;
+  const char *severity;
+
+  pid = fork_child (pl, &fd, NULL);
+  if (pid < 0) {
+    sfree (arg);
+    pthread_exit ((void *) 1);
+  }
+
+  fh = fdopen (fd, "w");
+  if (fh == NULL)
+  {
+    char errbuf[1024];
+    ERROR ("exec plugin: fdopen (%i) failed: %s", fd,
+	sstrerror (errno, errbuf, sizeof (errbuf)));
+    kill (pl->pid, SIGTERM);
+    pl->pid = 0;
+    close (fd);
+    sfree (arg);
+    pthread_exit ((void *) 1);
+  }
+
+  severity = "FAILURE";
+  if (n->severity == NOTIF_WARNING)
+    severity = "WARNING";
+  else if (n->severity == NOTIF_OKAY)
+    severity = "OKAY";
+
+  fprintf (fh,
+      "Severity: %s\n"
+      "Time: %u\n",
+      severity, (unsigned int) n->time);
+
+  /* Print the optional fields */
+  if (strlen (n->host) > 0)
+    fprintf (fh, "Host: %s\n", n->host);
+  if (strlen (n->plugin) > 0)
+    fprintf (fh, "Plugin: %s\n", n->plugin);
+  if (strlen (n->plugin_instance) > 0)
+    fprintf (fh, "PluginInstance: %s\n", n->plugin_instance);
+  if (strlen (n->type) > 0)
+    fprintf (fh, "Type: %s\n", n->type);
+  if (strlen (n->type_instance) > 0)
+    fprintf (fh, "TypeInstance: %s\n", n->type_instance);
+
+  fprintf (fh, "\n%s\n", n->message);
+
+  fflush (fh);
+  fclose (fh);
+
+  waitpid (pid, &status, 0);
+
+  DEBUG ("exec plugin: Child %i exited with status %i.",
+      pid, status);
+
+  sfree (arg);
+  pthread_exit ((void *) 0);
+  return (NULL);
+} /* void *exec_notification_one }}} */
+
+static int exec_init (void) /* {{{ */
+{
+  struct sigaction sa;
+
+  memset (&sa, '\0', sizeof (sa));
+  sa.sa_handler = sigchld_handler;
+  sigaction (SIGCHLD, &sa, NULL);
+
+  return (0);
+} /* int exec_init }}} */
+
+static int exec_read (void) /* {{{ */
 {
   program_list_t *pl;
 
   for (pl = pl_head; pl != NULL; pl = pl->next)
   {
     pthread_t t;
     pthread_attr_t attr;
 
-    if (pl->pid != 0)
+    /* Only execute `normal' style executables here. */
+    if ((pl->flags & PL_NORMAL) == 0)
       continue;
 
+    pthread_mutex_lock (&pl_lock);
+    /* Skip if a child is already running. */
+    if ((pl->flags & PL_RUNNING) != 0)
+    {
+      pthread_mutex_unlock (&pl_lock);
+      continue;
+    }
+    pl->flags |= PL_RUNNING;
+    pthread_mutex_unlock (&pl_lock);
+
     pthread_attr_init (&attr);
     pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
     pthread_create (&t, &attr, exec_read_one, (void *) pl);
   } /* for (pl) */
 
   return (0);
-} /* int exec_read */
+} /* int exec_read }}} */
+
+static int exec_notification (const notification_t *n)
+{
+  program_list_t *pl;
+  program_list_and_notification_t *pln;
+
+  for (pl = pl_head; pl != NULL; pl = pl->next)
+  {
+    pthread_t t;
+    pthread_attr_t attr;
+
+    /* Only execute `notification' style executables here. */
+    if ((pl->flags & PL_NOTIF_ACTION) == 0)
+      continue;
+
+    /* Skip if a child is already running. */
+    if (pl->pid != 0)
+      continue;
+
+    pln = (program_list_and_notification_t *) malloc (sizeof
+	(program_list_and_notification_t));
+    if (pln == NULL)
+    {
+      ERROR ("exec plugin: malloc failed.");
+      continue;
+    }
+
+    pln->pl = pl;
+    memcpy (&pln->n, n, sizeof (notification_t));
+
+    pthread_attr_init (&attr);
+    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
+    pthread_create (&t, &attr, exec_notification_one, (void *) pln);
+  } /* for (pl) */
+
+  return (0);
+} /* int exec_notification */
 
-static int exec_shutdown (void)
+static int exec_shutdown (void) /* {{{ */
 {
   program_list_t *pl;
   program_list_t *next;
 
   pl = pl_head;
   while (pl != NULL)
