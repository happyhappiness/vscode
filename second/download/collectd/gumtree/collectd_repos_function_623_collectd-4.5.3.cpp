static int notify_email_init (void)
{
  char server[MAXSTRING];

  auth_client_init();
  if (!(session = smtp_create_session ())) {
    ERROR ("notify_email plugin: cannot create SMTP session");
    return (-1);
  }

  smtp_set_monitorcb (session, monitor_cb, NULL, 1);
  smtp_set_hostname (session, hostname_g);
  ssnprintf(server, sizeof (server), "%s:%i",
      (smtp_host == NULL) ? DEFAULT_SMTP_HOST : smtp_host,
      smtp_port);
  smtp_set_server (session, server);

  if (smtp_user && smtp_password) {
    authctx = auth_create_context ();
    auth_set_mechanism_flags (authctx, AUTH_PLUGIN_PLAIN, 0);
    auth_set_interact_cb (authctx, authinteract, NULL);
  }

  if ( !smtp_auth_set_context (session, authctx)) {
    ERROR ("notify_email plugin: cannot set SMTP auth context");
    return (-1);   
  }

  return (0);
}