  struct passwd sp;
  char nambuf[2048];

  if (pl->pid != 0)
    return (-1);

  if ((create_pipe(fd_pipe_in) == -1)
      || (create_pipe(fd_pipe_out) == -1)
      || (create_pipe(fd_pipe_err) == -1))
    goto failed;

  sp_ptr = NULL;
  status = getpwnam_r (pl->user, &sp, nambuf, sizeof (nambuf), &sp_ptr);
  if (status != 0)
  {
    ERROR ("exec plugin: Failed to get user information for user ``%s'': %s",
        pl->user, sstrerror (errno, errbuf, sizeof (errbuf)));
    goto failed;
  }

  if (sp_ptr == NULL)
  {
    ERROR ("exec plugin: No such user: `%s'", pl->user);
    goto failed;
  }

  uid = sp.pw_uid;
  gid = sp.pw_gid;
  if (uid == 0)
  {
    ERROR ("exec plugin: Cowardly refusing to exec program as root.");
    goto failed;
  }

  /* The group configured in the configfile is set as effective group, because
   * this way the forked process can (re-)gain the user's primary group. */
  egid = -1;
  if (NULL != pl->group)
  {
    if ('\0' != *pl->group) {
      struct group *gr_ptr = NULL;
      struct group gr;

      status = getgrnam_r (pl->group, &gr, nambuf, sizeof (nambuf), &gr_ptr);
      if (0 != status)
      {
        ERROR ("exec plugin: Failed to get group information "
            "for group ``%s'': %s", pl->group,
            sstrerror (errno, errbuf, sizeof (errbuf)));
        goto failed;
      }
      if (NULL == gr_ptr)
      {
        ERROR ("exec plugin: No such group: `%s'", pl->group);
        goto failed;
      }

      egid = gr.gr_gid;
    }
    else
    {
      egid = gid;
    }
  } /* if (pl->group == NULL) */

  pid = fork ();
  if (pid < 0)
  {
    ERROR ("exec plugin: fork failed: %s",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    goto failed;
  }
  else if (pid == 0)
  {
    int fd_num;

    /* Close all file descriptors but the pipe end we need. */
    fd_num = getdtablesize ();
    for (int fd = 0; fd < fd_num; fd++)
    {
      if ((fd == fd_pipe_in[0])
          || (fd == fd_pipe_out[1])
          || (fd == fd_pipe_err[1]))
        continue;
      close (fd);
    }

    /* Connect the `in' pipe to STDIN */
    if (fd_pipe_in[0] != STDIN_FILENO)
    {
      dup2 (fd_pipe_in[0], STDIN_FILENO);
      close (fd_pipe_in[0]);
    }

    /* Now connect the `out' pipe to STDOUT */
    if (fd_pipe_out[1] != STDOUT_FILENO)
    {
      dup2 (fd_pipe_out[1], STDOUT_FILENO);
      close (fd_pipe_out[1]);
    }

    /* Now connect the `err' pipe to STDERR */
    if (fd_pipe_err[1] != STDERR_FILENO)
    {
      dup2 (fd_pipe_err[1], STDERR_FILENO);
      close (fd_pipe_err[1]);
    }

    set_environment ();

    /* Unblock all signals */
    reset_signal_mask ();

    exec_child (pl, uid, gid, egid);
    /* does not return */
  }

  close (fd_pipe_in[0]);
  close (fd_pipe_out[1]);
  close (fd_pipe_err[1]);

  if (fd_in != NULL)
    *fd_in = fd_pipe_in[1];
  else
    close (fd_pipe_in[1]);

  if (fd_out != NULL)
    *fd_out = fd_pipe_out[0];
  else
    close (fd_pipe_out[0]);

  if (fd_err != NULL)
    *fd_err = fd_pipe_err[0];
  else
    close (fd_pipe_err[0]);

  return (pid);

failed:
  close_pipe(fd_pipe_in);
  close_pipe(fd_pipe_out);
  close_pipe(fd_pipe_err);

  return (-1);
} /* int fork_child }}} */

static int parse_line (char *buffer) /* {{{ */
{
  if (strncasecmp ("PUTVAL", buffer, strlen ("PUTVAL")) == 0)
    return (handle_putval (stdout, buffer));
  else if (strncasecmp ("PUTNOTIF", buffer, strlen ("PUTNOTIF")) == 0)
    return (handle_putnotif (stdout, buffer));
  else
  {
    ERROR ("exec plugin: Unable to parse command, ignoring line: \"%s\"",
	buffer);
    return (-1);
  }
} /* int parse_line }}} */

static void *exec_read_one (void *arg) /* {{{ */
{
  program_list_t *pl = (program_list_t *) arg;
  int fd, fd_err, highest_fd;
  fd_set fdset, copy;
  int status;
  char buffer[1200];  /* if not completely read */
  char buffer_err[1024];
  char *pbuffer = buffer;
  char *pbuffer_err = buffer_err;

  status = fork_child (pl, NULL, &fd, &fd_err);
  if (status < 0)
  {
    /* Reset the "running" flag */
    pthread_mutex_lock (&pl_lock);
    pl->flags &= ~PL_RUNNING;
    pthread_mutex_unlock (&pl_lock);
    pthread_exit ((void *) 1);
  }
  pl->pid = status;

  assert (pl->pid != 0);

  FD_ZERO( &fdset );
  FD_SET(fd, &fdset);
  FD_SET(fd_err, &fdset);

  /* Determine the highest file descriptor */
  highest_fd = (fd > fd_err) ? fd : fd_err;

  /* We use a copy of fdset, as select modifies it */
  copy = fdset;

  while (1)
  {
    int len;

    status = select (highest_fd + 1, &copy, NULL, NULL, NULL);
    if (status < 0)
    {
      if (errno == EINTR)
        continue;
      break;
    }

    if (FD_ISSET(fd, &copy))
    {
      char *pnl;

      len = read(fd, pbuffer, sizeof(buffer) - 1 - (pbuffer - buffer));

      if (len < 0)
      {
        if (errno == EAGAIN || errno == EINTR)  continue;
        break;
      }
      else if (len == 0) break;  /* We've reached EOF */

      pbuffer[len] = '\0';

      len += pbuffer - buffer;
      pbuffer = buffer;

      while ((pnl = strchr(pbuffer, '\n')))
      {
        *pnl = '\0';
        if (*(pnl-1) == '\r' ) *(pnl-1) = '\0';

        parse_line (pbuffer);

        pbuffer = ++pnl;
      }
      /* not completely read ? */
      if (pbuffer - buffer < len)
      {
        len -= pbuffer - buffer;
        memmove(buffer, pbuffer, len);
        pbuffer = buffer + len;
      }
      else
        pbuffer = buffer;
    }
    else if (FD_ISSET(fd_err, &copy))
    {
      char *pnl;

      len = read(fd_err, pbuffer_err, sizeof(buffer_err) - 1 - (pbuffer_err - buffer_err));

      if (len < 0)
      {
        if (errno == EAGAIN || errno == EINTR)
          continue;
        break;
      }
      else if (len == 0)
      {
        /* We've reached EOF */
        NOTICE ("exec plugin: Program `%s' has closed STDERR.", pl->exec);

        /* Remove file descriptor form select() set. */
        FD_CLR (fd_err, &fdset);
        copy = fdset;
        highest_fd = fd;

        /* Clean up file descriptor */
        close (fd_err);
        fd_err = -1;
        continue;
      }

      pbuffer_err[len] = '\0';

      len += pbuffer_err - buffer_err;
      pbuffer_err = buffer_err;

      while ((pnl = strchr(pbuffer_err, '\n')))
      {
        *pnl = '\0';
        if (*(pnl-1) == '\r' ) *(pnl-1) = '\0';

        ERROR ("exec plugin: exec_read_one: error = %s", pbuffer_err);

        pbuffer_err = ++pnl;
      }
      /* not completely read ? */
      if (pbuffer_err - buffer_err < len)
      {
        len -= pbuffer_err - buffer_err;
        memmove(buffer_err, pbuffer_err, len);
        pbuffer_err = buffer_err + len;
      }
      else
        pbuffer_err = buffer_err;
    }
    /* reset copy */
    copy = fdset;
  }

  DEBUG ("exec plugin: exec_read_one: Waiting for `%s' to exit.", pl->exec);
  if (waitpid (pl->pid, &status, 0) > 0)
    pl->status = status;

  DEBUG ("exec plugin: Child %i exited with status %i.",
      (int) pl->pid, pl->status);

  pl->pid = 0;

  pthread_mutex_lock (&pl_lock);
  pl->flags &= ~PL_RUNNING;
  pthread_mutex_unlock (&pl_lock);

  close (fd);
  if (fd_err >= 0)
    close (fd_err);

  pthread_exit ((void *) 0);
  return (NULL);
} /* void *exec_read_one }}} */

static void *exec_notification_one (void *arg) /* {{{ */
{
  program_list_t *pl = ((program_list_and_notification_t *) arg)->pl;
  notification_t *n = &((program_list_and_notification_t *) arg)->n;
  int fd;
  FILE *fh;
  int pid;
  int status;
  const char *severity;

  pid = fork_child (pl, &fd, NULL, NULL);
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
    kill (pid, SIGTERM);
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
      "Time: %.3f\n",
      severity, CDTIME_T_TO_DOUBLE (n->time));

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

  for (notification_meta_t *meta = n->meta; meta != NULL; meta = meta->next)
  {
    if (meta->type == NM_TYPE_STRING)
      fprintf (fh, "%s: %s\n", meta->name, meta->nm_value.nm_string);
    else if (meta->type == NM_TYPE_SIGNED_INT)
      fprintf (fh, "%s: %"PRIi64"\n", meta->name, meta->nm_value.nm_signed_int);
    else if (meta->type == NM_TYPE_UNSIGNED_INT)
      fprintf (fh, "%s: %"PRIu64"\n", meta->name, meta->nm_value.nm_unsigned_int);
    else if (meta->type == NM_TYPE_DOUBLE)
      fprintf (fh, "%s: %e\n", meta->name, meta->nm_value.nm_double);
    else if (meta->type == NM_TYPE_BOOLEAN)
      fprintf (fh, "%s: %s\n", meta->name,
          meta->nm_value.nm_boolean ? "true" : "false");
  }

  fprintf (fh, "\n%s\n", n->message);

  fflush (fh);
  fclose (fh);

  waitpid (pid, &status, 0);

  DEBUG ("exec plugin: Child %i exited with status %i.",
      pid, status);

  if (n->meta != NULL)
    plugin_notification_meta_free (n->meta);
  n->meta = NULL;
  sfree (arg);
  pthread_exit ((void *) 0);
  return (NULL);
} /* void *exec_notification_one }}} */

static int exec_init (void) /* {{{ */
{
  struct sigaction sa = {
    .sa_handler = sigchld_handler
  };

  sigaction (SIGCHLD, &sa, NULL);

#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_SETUID) && defined(CAP_SETGID)
  if ((check_capability (CAP_SETUID) != 0) ||
      (check_capability (CAP_SETGID) != 0))
  {
    if (getuid () == 0)
      WARNING ("exec plugin: Running collectd as root, but the CAP_SETUID "
          "or CAP_SETGID capabilities are missing. The plugin's read function "
          "will probably fail. Is your init system dropping capabilities?");
    else
      WARNING ("exec plugin: collectd doesn't have the CAP_SETUID or "
          "CAP_SETGID capabilities. If you don't want to run collectd as root, "
          "try running \"setcap 'cap_setuid=ep cap_setgid=ep'\" on the "
          "collectd binary.");
  }
#endif

  return (0);
} /* int exec_init }}} */

static int exec_read (void) /* {{{ */
{
  for (program_list_t *pl = pl_head; pl != NULL; pl = pl->next)
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
    plugin_thread_create (&t, &attr, exec_read_one, (void *) pl);
    pthread_attr_destroy (&attr);
  } /* for (pl) */

  return (0);
} /* int exec_read }}} */

static int exec_notification (const notification_t *n, /* {{{ */
    user_data_t __attribute__((unused)) *user_data)
{
  program_list_and_notification_t *pln;

  for (program_list_t *pl = pl_head; pl != NULL; pl = pl->next)
  {
    pthread_t t;
    pthread_attr_t attr;

    /* Only execute `notification' style executables here. */
    if ((pl->flags & PL_NOTIF_ACTION) == 0)
      continue;

    /* Skip if a child is already running. */
    if (pl->pid != 0)
      continue;

    pln = malloc (sizeof (*pln));
    if (pln == NULL)
    {
      ERROR ("exec plugin: malloc failed.");
      continue;
    }

    pln->pl = pl;
    memcpy (&pln->n, n, sizeof (notification_t));

    /* Set the `meta' member to NULL, otherwise `plugin_notification_meta_copy'
     * will run into an endless loop. */
    pln->n.meta = NULL;
    plugin_notification_meta_copy (&pln->n, n);

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    plugin_thread_create (&t, &attr, exec_notification_one, (void *) pln);
    pthread_attr_destroy (&attr);
  } /* for (pl) */

  return (0);
} /* }}} int exec_notification */

static int exec_shutdown (void) /* {{{ */
{
  program_list_t *pl;
  program_list_t *next;

  pl = pl_head;
  while (pl != NULL)
  {
    next = pl->next;

    if (pl->pid > 0)
    {
      kill (pl->pid, SIGTERM);
      INFO ("exec plugin: Sent SIGTERM to %hu", (unsigned short int) pl->pid);
    }

    sfree (pl->user);
    sfree (pl);

    pl = next;
  } /* while (pl) */
  pl_head = NULL;

  return (0);
} /* int exec_shutdown }}} */

void module_register (void)
{
  plugin_register_complex_config ("exec", exec_config);
  plugin_register_init ("exec", exec_init);
  plugin_register_read ("exec", exec_read);
  plugin_register_notification ("exec", exec_notification,
      /* user_data = */ NULL);
  plugin_register_shutdown ("exec", exec_shutdown);
} /* void module_register */

/*
 * vim:shiftwidth=2:softtabstop=2:tabstop=8:fdm=marker
 */
