static int notify_email_init (void)
{
  char server[MAXSTRING];

  ssnprintf(server, sizeof (server), "%s:%i",
      (smtp_host == NULL) ? DEFAULT_SMTP_HOST : smtp_host,
      smtp_port);

  pthread_mutex_lock (&session_lock);

  auth_client_init();

  session = smtp_create_session ();
  if (session == NULL) {
    pthread_mutex_unlock (&session_lock);
    ERROR ("notify_email plugin: cannot create SMTP session");
    return (-1);
  }

  smtp_set_monitorcb (session, monitor_cb, NULL, 1);
  smtp_set_hostname (session, hostname_g);
  smtp_set_server (session, server);

  if (smtp_user && smtp_password) {
    authctx = auth_create_context ();
    auth_set_mechanism_flags (authctx, AUTH_PLUGIN_PLAIN, 0);
    auth_set_interact_cb (authctx, authinteract, NULL);
  }

  if ( !smtp_auth_set_context (session, authctx)) {
    pthread_mutex_unlock (&session_lock);
    ERROR ("notify_email plugin: cannot set SMTP auth context");
    return (-1);   
  }

  pthread_mutex_unlock (&session_lock);
  return (0);
}